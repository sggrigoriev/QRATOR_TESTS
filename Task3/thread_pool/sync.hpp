/*
 * Thread Pool events manager
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_SYNC_HPP
#define TASK3_SYNC_HPP

#include "locked.hpp"


class Sync {
public:
    typedef enum {SYN_THREAD_STOPS, SYN_NEW_TASK, SYN_TOTAL_STOP, SYN_SIZE} sync_event_t;
    Sync();
    ~Sync();
    void Notify(sync_event_t e);
    sync_event_t Wait();
private:
    int events_counter[SYN_SIZE];
    pthread_cond_t signal;
    pthread_mutex_t s_mutex;

    sync_event_t getEvent();

};


#endif //TASK3_SYNC_HPP
