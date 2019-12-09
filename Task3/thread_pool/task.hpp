/*
 * Abstract class for Tasks
 *
 Created by gsg on 09/12/2019.
*/

#ifndef TASK3_TASK_HPP
#define TASK3_TASK_HPP

class Task {
public:
    typedef enum {hi, norm, lo, sz} priority_t;
    typedef void(*task_t)();

    virtual ~Task() {};
    virtual void _do()=0;
};


#endif /* TASK3_TASK_HPP */
