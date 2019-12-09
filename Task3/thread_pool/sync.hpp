/*
 * Thread Pool events manager
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_SYNC_HPP
#define TASK3_SYNC_HPP


class Sync {
public:
    typedef enum {SYN_UNDEF, SYN_THREAD_STOPS, SYN_NEW_TASK, SYN_TOTAL_STOP} sync_event_t;
    Sync() {}
    ~Sync(){};
    void Notify(sync_event_t e){};
    sync_event_t Wait(){};


};


#endif //TASK3_SYNC_HPP
