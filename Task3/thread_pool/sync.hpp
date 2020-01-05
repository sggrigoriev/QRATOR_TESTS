/*
 * Thread Pool events sync object
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_SYNC_HPP
#define TASK3_SYNC_HPP

#include "pthread.h"

#define SYNC_TOTAL_STOP false
#define SYNC_NEW_TASK true

class Sync {
public:
    Sync();
    ~Sync();
    void NotifyNewTask();
    void NotifyStop();
    bool Wait();            //Returns SYNC_TOTAL_STOP or SYNC_NEW_TASK
private:
    pthread_cond_t t_signal;
    pthread_mutex_t t_mutex;

    bool total_stop;
    size_t tasks_amount;
    size_t workers_wait;

    void send_signal();     //NB! not thread protected!
};


#endif //TASK3_SYNC_HPP
