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
        bool e = starter->syn.Wait();
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wswitch-bool"
        switch (e) {
            case SYNC_NEW_TASK: {
                Task* t = starter->q.get();
                if(t) t->_do();
            }
                break;
            case SYNC_TOTAL_STOP:
            default:
                pthread_exit(NULL);
        }
#pragma GCC diagnostic pop
    }
}
