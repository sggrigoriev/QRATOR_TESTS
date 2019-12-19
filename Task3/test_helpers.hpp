/*
 Created by gsg on 13/12/2019.
*/

#ifndef TASK3_TEST_HELPERS_H
#define TASK3_TEST_HELPERS_H

#include <unistd.h>
#include <pthread.h>

#include <cstddef>
#include <vector>
#include <set>
#include <string>

#include "json_file_proc.h"

#include "task.hpp"

class Result: public std::vector<int> {
public:
    Result(size_t size){ pthread_mutex_init(&own, NULL); set(size);}
    ~Result() { pthread_mutex_destroy(&own);}
    void add(int res) {pthread_mutex_lock(&own); push_back(res);pthread_mutex_unlock(&own);}
private:
    pthread_mutex_t own;
    void set(size_t size) { for(size_t i = 0;i<size;i++) push_back(-1);}
};

class SlowAnswer: public Task {
public:
    SlowAnswer(time_t sec_interval, int num, Result& res): delay(sec_interval), result(res), number(num) {}
    virtual void _do() { result.add(number); sleep(delay);  }
private:
    unsigned int delay;
    int number;
    Result& result;
};

typedef std::vector<SlowAnswer> sa_array_t;

class Set: public std::set<int> {
public:
    Set() {}
    explicit Set(Result& res) {for(size_t i = 0; i < res.size(); i++) if(res[i]>=0)insert(res[i]); }
    bool operator== (const Set& other) const;
    void printIt();
};

class Vector: public std::vector<int> {
public:
    Vector() {}
    explicit Vector(Result& res) {for(size_t i = 0; i < res.size(); i++) if(res[i]>=0)push_back(res[i]); }
    bool operator== (const Vector& other) const;
    void printIt();
};

class Test {
public:
    explicit Test(cJSON* test_item, size_t itemNo);
    bool valid() const { return is_valid; }
    void run();

private:
    typedef struct task_s {
        Task::priority_t prt;
        time_t work_time;
        bool is_valid;
        task_s(cJSON* arr_item, int testNo);
        void printIt();
    } task_t;
    typedef std::vector<task_t> tasks_array_t;

    bool is_valid;

    size_t test_number;
    char* test_name;
    char* test_expected;
    tasks_array_t tasks_array;
    size_t workers_amount;
    unsigned delay_before_stop;
    Set s_result;
    Vector v_result;
    bool is_vector_result;
    int stop_after;

    void print_conditions();
};

class TestArray: public std::vector<Test> {
public:
    explicit TestArray(const std::string& fname);
    ~TestArray() { cj_free(ts); }
    bool valid() const { return is_valid; };
private:
    bool is_valid;
    cJSON* ts;
};

#endif /* TASK3_TEST_HELPERS_H */
