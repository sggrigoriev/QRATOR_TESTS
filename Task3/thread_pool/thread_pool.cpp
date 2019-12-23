/*
 Created by gsg on 09/12/2019.
*/
#include <cassert>
#include <zconf.h>

#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t workers_amount) throw(TP_exception)
        :all_stops(false), q(syn) {
    assert(workers_amount);

    while(workers_amount--) {
        Worker* wrk = new Worker(syn, q);
        w.push_back(wrk);
        wrk->run();
    }
 }

 ThreadPool::~ThreadPool() {
     for(std::vector<Worker*>::iterator i = w.begin(); i != w.end(); ++i) {
         delete (*i);
     }
}

bool ThreadPool::Enqueue(Task& t, Task::priority_t p) throw(TP_exception) {
    assert((p >= Task::hi) && (p <= Task::lo));
    if(all_stops) return all_stops;

    q.add(&t,p);

    return true;
}

void ThreadPool::Stop() {
    all_stops = true;
    q.stop();
    for(std::vector<Worker*>::iterator i = w.begin(); i != w.end(); ++i) {
        syn.Notify(Sync::SYN_TOTAL_STOP);
    }
}
