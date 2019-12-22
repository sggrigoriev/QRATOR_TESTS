/*
 * Thread Pool's dispatcher thread.
 * Waits for new tasks and/or for vacant workers to pass a task to worker
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_MANAGER_HPP
#define TASK3_MANAGER_HPP

#include "task.hpp"
#include "sync.hpp"
#include "tp_queue.hpp"
#include "workers.hpp"

class Manager: public Task {
public:
    Manager(Sync& _syn, PrtTpQueue& _q, Workers& _wrk): syn(_syn), q(_q), wrk(_wrk) {}
    virtual ~Manager() {};
    void virtual _do();
private:
    Sync& syn;
    PrtTpQueue& q;
    Workers& wrk;

};



#endif //TASK3_MANAGER_HPP
