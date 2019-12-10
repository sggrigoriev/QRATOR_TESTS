/*
 * Wrapper for task start
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_THREAD_STARTER_HPP
#define TASK3_THREAD_STARTER_HPP

#include <pthread.h>

#include "tp_exception.hpp"
#include "task.hpp"
#include "sync.hpp"
#include "locked.hpp"

class ThreadStarter {
public:
    explicit ThreadStarter(Task& t): task(t) {};
    bool run() throw (TP_exception);
    void stop();
protected:
    Task& task;


    pthread_t id;
    pthread_attr_t attr;

    static void* thread_proc(void* param);
};

class TaskStarter: public ThreadStarter {
public:
    TaskStarter(Task& t, Sync& _syn): ThreadStarter(t), syn(_syn), vacant(true) {};
    bool run() throw (TP_exception);
    bool isVacant() const { return vacant.get(); }
private:
    Sync& syn;
    Locked<bool> vacant;

    static void* thread_proc(void* param);
};


#endif //TASK3_THREAD_STARTER_HPP
