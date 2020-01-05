/*
 * Main class with external interfaces
 *
 Created by gsg on 09/12/2019.
*/

#ifndef TASK3_THREAD_POOL_HPP
#define TASK3_THREAD_POOL_HPP

#include "tp_queue.hpp"
#include "sync.hpp"
#include "task.hpp"

class Worker;

class ThreadPool {
public:
    explicit ThreadPool(size_t workers_amount);
    ~ThreadPool();
    bool Enqueue(Task& t, Task::priority_t p);
    void Stop();

private:
    bool all_stops;
    Sync syn;
    PrtTpQueue q;

    std::vector<Worker*> w;
};



#endif //TASK3_THREAD_POOL_HPP
