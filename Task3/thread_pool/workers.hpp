/*
 * Serves running tasks
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_WORKERS_HPP
#define TASK3_WORKERS_HPP

#include <cstdlib>
#include <list>

#include "task.hpp"
#include "tp_exception.hpp"

#include "thread_starter.hpp"


class Workers {
public:
    typedef enum {CLEAN, CLEAN_ALL} clean_t;
    Workers(size_t amt, Sync& _syn): size(amt), syn(_syn){}
    ~Workers() {}

    void runTask(Task& t) throw(TP_exception);
    void cleanClearing(clean_t mode);
    bool vacant() const {return (size-running.size()) > 0;}
private:
    typedef std::list<TaskStarter*> ts_list_t;

    size_t size;
    ts_list_t running;
    Sync& syn;
};


#endif //TASK3_WORKERS_HPP
