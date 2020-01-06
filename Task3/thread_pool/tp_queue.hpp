/*
 * ThreadPool's queue
 * Adds new tasks
 * Gets the task accordingly to the rules
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_TP_QUEUE_HPP
#define TASK3_TP_QUEUE_HPP


#include <cstdlib>
#include <queue>
#include <pthread.h>

#include "task.hpp"
#include "sync.hpp"

class TpQueue {
public:
    virtual ~TpQueue() {}
    virtual void add(Task* t, Task::priority_t p);
    Task* get(Task::priority_t p);
    bool empty(Task::priority_t p) const;
    size_t amount() const { return q[Task::lo].size() + q[Task::norm].size() + q[Task::hi].size();}
protected:
    std::queue<Task*> q[Task::sz];
};

class PrtTpQueue: private TpQueue {
public:
    PrtTpQueue(Sync& _syn): hi_in_a_row(0), syn(_syn) {pthread_mutex_init(&q_mutex, NULL);}
    virtual ~PrtTpQueue() { pthread_mutex_destroy(&q_mutex); }

    void add(Task* t, Task::priority_t p);
    Task* get();
    void stop();
private:
    int hi_in_a_row;
    pthread_mutex_t q_mutex;

    Sync& syn;
};


#endif //TASK3_TP_QUEUE_HPP
