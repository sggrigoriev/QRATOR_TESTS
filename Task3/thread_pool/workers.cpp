/*
 Created by gsg on 10/12/2019.
*/

#include <cassert>
#include <iostream>
#include <zconf.h>

#include "workers.hpp"

void Worker::run() throw(TP_exception) {
    if(pthread_attr_init(&attr)) throw TP_exception("Worker::run: pthread_attr_init error. Abort.");
    if(pthread_attr_setschedpolicy(&attr, SCHED_FIFO)) throw TP_exception("Worker::run: pthread_attr_setschedpolicy error. Abort.");

    if(pthread_create(&id, &attr, &Worker::thread_proc, (void*)this)) throw TP_exception("Worker::run: pthread_create error. Abort.");
}

void Worker::stop() {
    void *ret;
    pthread_join(id, &ret);
    pthread_attr_destroy(&attr);
}

void* Worker::thread_proc(void* param) {
    Worker *starter = static_cast<Worker *>(param);

    while(true) {
        Sync::sync_event_t e = starter->syn.Wait();
        switch (e) {
            case Sync::SYN_NEW_TASK: {
                Task &t = starter->q.get();
                t._do();
            }
                break;
            case Sync::SYN_TOTAL_STOP:
            default:
                pthread_exit(NULL);
        }
    }
}
