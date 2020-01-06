/*
 Created by gsg on 10/12/2019.
*/

#include <iostream>
#include <cassert>

#include "tp_queue.hpp"

void TpQueue::add(Task* t, Task::priority_t p) {
    assert((p >= Task::hi) && (p < Task::sz));
    q[p].push(t);
}
Task* TpQueue::get(Task::priority_t p) {
    assert((p >= Task::hi) && (p < Task::sz) && !q[p].empty());
    Task* ret = q[p].front();
    q[p].pop();
    return ret;
}
bool TpQueue::empty(Task::priority_t p) const {
    assert((p >= Task::hi) && (p < Task::sz));
    return q[p].empty();
}


PrtTpQueue::PrtTpQueue(): hi_in_a_row(0) {
    pthread_mutex_init(&q_mutex, NULL);
    pthread_mutex_init(&t_mutex, NULL);
    pthread_cond_init (&t_signal, NULL);
    total_stop = false;
    workers_wait = 0;
    tasks_amt = 0;
}
PrtTpQueue::~PrtTpQueue() {
    pthread_mutex_destroy(&q_mutex);
    pthread_mutex_destroy(&t_mutex);
    pthread_cond_destroy(&t_signal);
}
/*
 Приоритеты обрабатываются следующим образом:
    low-задачи не выполняются никогда, пока в очереди есть хотя бы одна задача с другим приоритетом.
    на 3 high-задачи выполняется 1 normal-задача.
    Данная логика относится только к выборке задачи из очереди, уже запущенные задачи приоритизировать не требуется.

    get Low:    q[Task::hi].empty()&&q[Task::norm].empty()&&!q[Task::lo].empty()
    get Norm:   q[Task::hi].empty()&&!&q[Task::norm].empty() ||
                3 hi взяли полряд && !q[Task::norm].empty()
    getHi:      !q[Task::hi].empty() && !(3 hi взяли полряд && !q[Task::norm].empty())
 */

void PrtTpQueue::add(Task* t, Task::priority_t p) {
    size_t amt=0;
    pthread_mutex_lock(&q_mutex);
    try {
        TpQueue::add(t, p);
    }
    catch (...) {
        std::cerr << "PrtTpQueue::add: System exception. Task is not added.\n";
        pthread_mutex_unlock(&q_mutex);
        return;
    }
    tasks_amt++;
    NotifyNewTask();
    pthread_mutex_unlock(&q_mutex);
}

Task* PrtTpQueue::get() {
    Task* ret = NULL;
    pthread_mutex_lock(&q_mutex);
    if(!TpQueue::empty(Task::hi)) {
        if(hi_in_a_row < 3) {
            ret = TpQueue::get(Task::hi);
            hi_in_a_row++;
        }
        else if(!TpQueue::empty(Task::norm)) {
            hi_in_a_row = 0;
            ret = TpQueue::get(Task::norm);
        }
        else {
            ret = TpQueue::get(Task::hi);
            hi_in_a_row++;
        }
    }
    else if(!TpQueue::empty(Task::norm)) {
        hi_in_a_row = 0;
        ret = TpQueue::get(Task::norm);
    }
    else if(!TpQueue::empty(Task::lo)) {
        hi_in_a_row = 0;
        ret = TpQueue::get(Task::lo);
    }

    if(ret) tasks_amt--;

    pthread_mutex_unlock(&q_mutex);
    return ret;
}

void PrtTpQueue::stop() {
    pthread_mutex_lock(&q_mutex);
    for(int i = 0; i < Task::sz; i++) {
        while(!q->empty())q[i].pop();
    }
    tasks_amt = 0;
    pthread_mutex_unlock(&q_mutex);
    NotifyStop();
}

bool PrtTpQueue::queue_empty() {
    bool ret;
    pthread_mutex_lock(&q_mutex);
    ret = empty(Task::lo) && empty(Task::norm) && empty(Task::hi);
    pthread_mutex_unlock(&q_mutex);
    return ret;
}

void PrtTpQueue::NotifyNewTask() {
    pthread_mutex_lock(&t_mutex);
    //amount correction because of possible raice after wait
    send_all();
    pthread_mutex_unlock(&t_mutex);
}

void PrtTpQueue::NotifyStop() {
    pthread_mutex_lock(&t_mutex);
    total_stop = true;
    send_all();
    pthread_mutex_unlock(&t_mutex);
}

bool PrtTpQueue::Wait() {
    bool ret = SYNC_NEW_TASK;
    pthread_mutex_lock(&t_mutex);

    if(total_stop) {
        ret = SYNC_TOTAL_STOP;
        pthread_mutex_unlock(&t_mutex);
        return ret;
    }
    if(tasks_amt > 0) {
        ret = SYNC_NEW_TASK;
        pthread_mutex_unlock(&t_mutex);
        return ret;
    }
      //!stop && !tasks_amount
    workers_wait++;

    while(!total_stop && !tasks_amt)
        pthread_cond_wait(&t_signal, &t_mutex);

    workers_wait = workers_wait - 1;

    if(total_stop) {
        ret = SYNC_TOTAL_STOP;
    }
    else/* if(tasks_amt > 0) */{
        ret = SYNC_NEW_TASK;
    }

    pthread_mutex_unlock(&t_mutex);
    return ret;
}

void PrtTpQueue::send_signal() {
    if(workers_wait > 0)
        pthread_cond_signal(&t_signal);
}

void PrtTpQueue::send_all() {
    if(workers_wait > 0)
        pthread_cond_broadcast(&t_signal);
}