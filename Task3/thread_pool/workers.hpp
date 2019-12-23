/*
 * Serves running tasks
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_WORKERS_HPP
#define TASK3_WORKERS_HPP

#include <cstdlib>

#include "tp_exception.hpp"
#include "sync.hpp"
#include "tp_queue.hpp"


class Worker {
public:
    Worker(Sync& _syn,  PrtTpQueue& _q): syn(_syn), q(_q) {}
    ~Worker() { stop(); }

    void run() throw(TP_exception);

private:
    Sync& syn;
    PrtTpQueue& q;

    pthread_t id;
    pthread_attr_t attr;

    static void* thread_proc(void* param);
    void stop();
};


#endif //TASK3_WORKERS_HPP
