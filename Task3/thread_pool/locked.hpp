/*
 * Wrapper for thread-protected variables (no boost, no c++ 11)
 *
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_LOCKED_HPP
#define TASK3_LOCKED_HPP

#include "pthread.h"

template <typename value_type>
class Locked {
public:
    Locked(value_type val): value(val) { pthread_mutex_init(&mutex, NULL);}
    ~Locked() {
        pthread_mutex_destroy(&mutex);
    }
    void set(value_type val) {
        pthread_mutex_lock(&mutex);
        value = val;
        pthread_mutex_unlock(&mutex);
    }
    value_type get() const {
        value_type ret;
        pthread_mutex_lock((pthread_mutex_t*)&mutex);
        ret = value;
        pthread_mutex_unlock((pthread_mutex_t*)&mutex);
        return ret;
    }
private:
    value_type value;
    pthread_mutex_t mutex;
};

#endif /* TASK3_LOCKED_HPP */
