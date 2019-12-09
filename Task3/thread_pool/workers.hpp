/*
 * Serves running tasks
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_WORKERS_HPP
#define TASK3_WORKERS_HPP

#include <cstdlib>

#include "task.hpp"
#include "tp_exception.hpp"


class Workers {
public:
    Workers(size_t amt){}
    ~Workers(){}
    void killall() {}
    void runTask(Task& t) throw(TP_exception){}
    bool vacant() const {}
};


#endif //TASK3_WORKERS_HPP
