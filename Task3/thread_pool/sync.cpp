/*
 Created by gsg on 10/12/2019.
*/

#include "sync.hpp"

Sync::Sync() {
    pthread_mutex_init(&t_mutex, NULL);
    pthread_cond_init (&t_signal, NULL);
    total_stop = false;
    tasks_amount = 0;
    workers_wait = 0;
}

Sync::~Sync() {
    pthread_mutex_destroy(&t_mutex);
    pthread_cond_destroy(&t_signal);
}

void Sync::NotifyNewTask() {
    pthread_mutex_lock(&t_mutex);
    tasks_amount++;
    send_signal();
    pthread_mutex_unlock(&t_mutex);
}

void Sync::NotifyStop() {
    pthread_mutex_lock(&t_mutex);
    total_stop = true;
    send_signal();
    pthread_mutex_unlock(&t_mutex);
}

bool Sync::Wait() {
    bool ret;
    pthread_mutex_lock(&t_mutex);
    if(total_stop) {
        ret = SYNC_TOTAL_STOP;
    }
    else if(tasks_amount > 0) {
        tasks_amount--;
        ret = SYNC_NEW_TASK;
    }
    else {      //!stop && !tasks_amount
        workers_wait++;

        while(!total_stop && !tasks_amount)
            pthread_cond_wait(&t_signal, &t_mutex);

        workers_wait--;
        if(total_stop) {
            ret = SYNC_TOTAL_STOP;
        }
        else { //tasks_amount > 0
            tasks_amount--;
            ret = SYNC_NEW_TASK;
        }
    }
    pthread_mutex_unlock(&t_mutex);
    return ret;
}

void Sync::send_signal() {
    if(workers_wait > 0)
        pthread_cond_broadcast(&t_signal);
}