/*
 * Main class with external interfaces
 *
 Created by gsg on 09/12/2019.
*/

#ifndef TASK3_THREAD_POOL_HPP
#define TASK3_THREAD_POOL_HPP

#include <cstdlib>

#include "tp_exception.hpp"
#include "task.hpp"
#include "tp_queue.hpp"
#include "sync.hpp"
#include "thread_starter.hpp"
#include "manager.hpp"
#include "workers.hpp"

class ThreadPool {
public:
    explicit ThreadPool(size_t workers_amount) throw(TP_exception);
    ~ThreadPool(){};
    bool Enqueue(Task& t, Task::priority_t p) throw(TP_exception);
    void Stop();

private:
    bool all_stops;
    Sync syn;
    PrtTpQueue q;
    Workers wrk;
    Manager mgr;
    ThreadStarter ts;
};



#endif //TASK3_THREAD_POOL_HPP
