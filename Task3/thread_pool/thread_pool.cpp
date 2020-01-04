/*
 Created by gsg on 09/12/2019.
*/
#include <cassert>
#include <zconf.h>
#include <iostream>

#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t workers_amount)
        :all_stops(false), q(syn) {
    assert(workers_amount);
    try {
        while (workers_amount--) {
            Worker *wrk = new Worker(syn, q);
            wrk->run();
            w.push_back(wrk);
        }
    }
    catch (TP_exception& e) {
        std::cerr << e.what() << " ThreadPool aborted\n";
        all_stops = true;
    }
    catch (...) {
        std::cerr << "ThreadPool::ThreadPool: System exception happened. ThreadPool aborted.\n";
        all_stops = true;
    }
 }

ThreadPool::~ThreadPool() {
    if(!all_stops) Stop();
    for(std::vector<Worker*>::iterator i = w.begin(); i != w.end(); ++i) {
        delete (*i);
    }
}

bool ThreadPool::Enqueue(Task& t, Task::priority_t p) {
    assert((p >= Task::hi) && (p <= Task::lo));

    if(all_stops) return false;
    q.add(&t, p);

    return true;
}

void ThreadPool::Stop() {
    all_stops = true;
    q.stop();
}
