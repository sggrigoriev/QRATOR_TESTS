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

#define SYNC_TOTAL_STOP false
#define SYNC_NEW_TASK true

class TpQueue {
public:
    virtual ~TpQueue() {}
    virtual void add(Task* t, Task::priority_t p);
    Task* get(Task::priority_t p);
    bool empty(Task::priority_t p) const;
protected:
    std::queue<Task*> q[Task::sz];
};

class PrtTpQueue: private TpQueue {
public:
    PrtTpQueue();
    virtual ~PrtTpQueue();

    void add(Task* t, Task::priority_t p);
    Task* get();
    void stop();
    bool Wait();            //Returns SYNC_TOTAL_STOP or SYNC_NEW_TASK
private:
    int hi_in_a_row;
    pthread_mutex_t q_mutex;

    void NotifyNewTask();
    void NotifyStop();

    pthread_cond_t t_signal;
    pthread_mutex_t t_mutex;

    volatile bool total_stop;
    volatile size_t workers_wait;
    volatile int tasks_amt;

    void send_all();
};


#endif //TASK3_TP_QUEUE_HPP
