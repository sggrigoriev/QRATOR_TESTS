/*
 * Serves running tasks
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_WORKERS_HPP
#define TASK3_WORKERS_HPP

#include "tp_exception.hpp"
#include "tp_queue.hpp"


class Worker {
public:
    Worker(PrtTpQueue& _q): q(_q) {}
    ~Worker() { stop(); }

    void run() throw(TP_exception);

private:
    PrtTpQueue& q;

    pthread_t id;
    pthread_attr_t attr;

    static void* thread_proc(void* param) throw(TP_exception);
    void stop();
};


#endif //TASK3_WORKERS_HPP
