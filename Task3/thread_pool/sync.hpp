/*
 * Thread Pool events sync object
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_SYNC_HPP
#define TASK3_SYNC_HPP

#include "pthread.h"

class Sync {
public:
    typedef enum {SYN_TOTAL_STOP, SYN_NEW_TASK, SYN_SIZE} sync_event_t;
    Sync();
    ~Sync();
    void Notify(sync_event_t e);
    sync_event_t Wait();
private:
    int events_counter[SYN_SIZE];
    pthread_cond_t signal;
    pthread_mutex_t s_mutex;
    pthread_mutex_t ec_mutex; //for events counter

    sync_event_t getEvent();

};


#endif //TASK3_SYNC_HPP
