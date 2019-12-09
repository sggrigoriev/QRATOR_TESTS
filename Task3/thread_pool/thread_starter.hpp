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
    explicit ThreadStarter(Task& t, Sync& _syn);
    bool run() throw (TP_exception);
    bool isVacant() const { return vacant.get(); }
private:
    Task& task;
    Sync& syn;
    Locked<bool> vacant;

    pthread_t id;
    pthread_attr_t attr;

    static void* thread_proc(void* param);
};


#endif //TASK3_THREAD_STARTER_HPP
