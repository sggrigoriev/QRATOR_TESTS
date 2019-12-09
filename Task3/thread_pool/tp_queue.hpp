/*
 * ThreadPool's queue
 * Adds new tasks
 * Gets the task accirdingly to the rules
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_TP_QUEUE_HPP
#define TASK3_TP_QUEUE_HPP


#include <cstdlib>

#include <queue>
#include <vector>
#include <cassert>

#include "task.hpp"

class TpQueue {
public:
    virtual void add(Task* t, Task::priority_t p);
    Task& get(Task::priority_t p);
    bool empty(Task::priority_t p) const; //For all if p == Task::sz
protected:
    std::queue<Task*> q[Task::sz];
};

class PrtTpQueue: private TpQueue {
public:
    PrtTpQueue(): hi_in_a_row(0) {}
    void add(Task* t, Task::priority_t p) {TpQueue::add(t, p);}
    Task& get();
    bool empty() const;
private:
    int hi_in_a_row;

    bool each3rdRule();
};


#endif //TASK3_TP_QUEUE_HPP
