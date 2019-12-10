/*
 Created by gsg on 09/12/2019.
*/
#include <cassert>
#include <zconf.h>

#include "thread_pool.hpp"


ThreadPool::ThreadPool(size_t workers_amount) throw(TP_exception)
        : wrk(workers_amount, syn), mgr(syn, q, wrk), ts(mgr)  {
    assert(workers_amount);
    all_stops = false;

    if(!ts.run())
        throw TP_exception("ThreadPool::ThreadPool: Error on Manager() start. Aborted.");
}

bool ThreadPool::Enqueue(Task& t, Task::priority_t p) throw(TP_exception) {
    assert((p >= Task::hi) && (p <= Task::lo));
    if(all_stops) return all_stops;

    q.add(&t,p);
    syn.Notify(Sync::SYN_NEW_TASK);

    return true;
}

void ThreadPool::Stop() {
    all_stops = true;
    syn.Notify(Sync::SYN_TOTAL_STOP);
    ts.stop();
    wrk.cleanClearing(Workers::CLEAN_ALL);
}
