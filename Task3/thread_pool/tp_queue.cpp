/*
 Created by gsg on 10/12/2019.
*/

#include "tp_queue.hpp"

void TpQueue::add(Task* t, Task::priority_t p) {
    assert((p >= Task::hi) && (p < Task::sz));
    q[p].push(t);
}
Task& TpQueue::get(Task::priority_t p) {
    assert((p >= Task::hi) && (p < Task::sz) && !q[p].empty());
    Task& ret = *q[p].front();
    q[p].pop();
    return ret;
}
bool TpQueue::empty(Task::priority_t p) const {
    assert((p >= Task::hi) && (p < Task::sz));
    return q[p].empty();
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
    pthread_mutex_lock(&q_mutex);
    TpQueue::add(t, p);
    pthread_mutex_unlock(&q_mutex);

    syn.Notify(Sync::SYN_NEW_TASK);
}

Task& PrtTpQueue::get() {
    Task* ret = NULL;
    pthread_mutex_lock(&q_mutex);
    if(!TpQueue::empty(Task::hi)) {
        if(hi_in_a_row < 3) {
            ret = &TpQueue::get(Task::hi);
            hi_in_a_row++;
        }
        else if(!TpQueue::empty(Task::norm)) {
            hi_in_a_row = 0;
            ret = &TpQueue::get(Task::norm);
        }
        else {
            ret = &TpQueue::get(Task::hi);
            hi_in_a_row++;
        }
    }
    else if(!TpQueue::empty(Task::norm)) {
        hi_in_a_row = 0;
        ret = &TpQueue::get(Task::norm);
    }
    else if(!TpQueue::empty(Task::lo)) {
        hi_in_a_row = 0;
        ret = &TpQueue::get(Task::lo);
    }
    pthread_mutex_unlock(&q_mutex);
    return *ret;
}

void PrtTpQueue::stop() {
    pthread_mutex_lock(&q_mutex);

    for(int i = 0; i < Task::sz; i++) {
        while(!q->empty())q[i].pop();
    }

    pthread_mutex_unlock(&q_mutex);

}

