/*
 Created by gsg on 13/12/2019.
*/

#include <iostream>
#include <cstdlib>
#include <zconf.h>
#include "json_file_proc.h"
#include "thread_pool.hpp"

#include "test_helpers.hpp"

static const char* t_name = "name";
static const char* t_expected = "expected";
static const char* t_tasks = "tasks";
static const char* t_priority = "priority";
static const char* t_workTimeSec = "workTimeSec";
static const char* t_workersAmount = "workersAmount";
static const char* t_delaySecBeforeStop = "delaySecBeforeStop";
static const char* t_resultSet = "resultSet";
static const char* t_result = "result";
static const char* t_stop_after = "stop_after";

bool Set::operator== (const Set& other) const {
    if(this == &other) return true;
    if(this->size() != other.size()) return false;
    for(std::set<int>::iterator tit = this->begin(); tit != this->end(); ++tit) {
        std::set<int>::iterator oit = other.find(*tit);
        if(oit == other.end()) return false;
    }
    return true;
}
void Set::printIt() {
    std::cout << "{";
    for(Set::iterator it = begin(); it != end(); ++it) std::cout << " " << *it;
    std::cout << " }";
}

bool Vector::operator== (const Vector& other) const {
    if(this == &other) return true;
    if(this->size() != other.size()) return false;
    for(size_t i = 0; i < this->size(); i++) {
        if(this->at(i) != other.at(i)) return false;
    }
    return true;
}
void Vector::printIt() {
    std::cout << "[";
    for(Vector::iterator it = begin(); it != end(); ++it) std::cout << " " << *it;
    std::cout << " ]";
}

static const std::string prt_names_array[Task::sz] = {"hi", "norm", "lo"};

Test::task_s::task_s(cJSON* arr_item, int testNo): prt(Task::sz), work_time(0), is_valid(false) {
    char* prt_name;

    if(!get_string(arr_item, testNo, t_priority, &prt_name)) return;

    for(int i = Task::hi; i < Task::sz; i++) {
        if(prt_names_array[i] == std::string(prt_name)) {
            prt = static_cast<Task::priority_t>(i);
            break;
        }
    }
    if(prt == Task::sz) return;

    unsigned wt;
    if(!get_uint(arr_item, testNo, t_workTimeSec, &wt)) return;

    work_time = static_cast<time_t>(wt);
    is_valid = true;
}
void Test::task_s::printIt() {
    std::cout << "priority = " << prt_names_array[prt] << " work time = " << work_time << "\n";
}

Test::Test(cJSON* test_item, size_t itemNo)
    : is_valid(false), test_number(itemNo), test_name(NULL), test_expected(NULL),
    workers_amount(0),  delay_before_stop(0), is_vector_result(true), stop_after(-1) {

    if(!get_string(test_item, itemNo, t_name, &test_name)) return;

    if(!get_string(test_item, itemNo, t_expected, &test_expected)) return;

    cJSON* test_array = find(test_item, itemNo, t_tasks, cJSON_Array);
    if(!test_array) return;

    for(int i = 0; i < cJSON_GetArraySize(test_array); i++) {
        task_t t(cJSON_GetArrayItem(test_array, i), itemNo);
        if(!t.is_valid) return;
        tasks_array.push_back(t);
    }

    unsigned wa;
    if(!get_uint(test_item, itemNo, t_workersAmount, &wa)) return;
    workers_amount = static_cast<size_t>(wa);

    if(!get_uint(test_item, itemNo, t_delaySecBeforeStop, &delay_before_stop)) return;

    cJSON* jset = cJSON_GetObjectItem(test_item, t_resultSet);
    cJSON* jarr = cJSON_GetObjectItem(test_item, t_result);
    if(jset && jarr) {
        std::cout << "Data error in Test# " << itemNo << ": '" << t_resultSet << "' and '" << t_result << "' can't be set together!\n";
        return;
    }
    if(!jset && !jarr) {
        std::cout << "Data error in Test# " << itemNo << ": '" << t_resultSet << "' or '" << t_result << "' should be set!\n";
        return;
    }
    int* a;
    int a_size;
    if(jset) {
        if(!get_int_array(test_item, itemNo, t_resultSet, &a, &a_size)) return;
        for(int i = 0; i < a_size; i++) {
            s_result.insert(a[i]);
            is_vector_result = false;
        }
    }
    if(jarr) {
        if(!get_int_array(test_item, itemNo, t_result, &a, &a_size)) return;
        for(int i = 0; i < a_size; i++) {
            v_result.push_back(a[i]);
            is_vector_result = true;
        }
    }
    free(a);

    if(cJSON_GetObjectItem(test_item, t_stop_after)) {
        unsigned sa;
        if (!get_uint(test_item, itemNo, t_stop_after, &sa)) return;
        stop_after = static_cast<int>(sa);
    }

    is_valid = true;
}

void Test::run() {
    print_conditions();

    Result result(tasks_array.size());
    sa_array_t sa_arr;
    for(size_t i = 0; i < tasks_array.size(); i++) {
        sa_arr.push_back(SlowAnswer(tasks_array[i].work_time, i, result));
    }
    try {
        ThreadPool tp(workers_amount);

        bool stop_called = false;
        for (size_t i = 0; i < tasks_array.size(); i++) {
            bool ret = tp.Enqueue(sa_arr[i], tasks_array[i].prt);
            if (stop_after == i) {
                if (delay_before_stop) sleep(delay_before_stop);
                tp.Stop();
                stop_called = true;
            }
            if (!ret && !stop_called) {
                std::cout << "Enque() returns unexpected false. !!!Failed!!!\n";
                return;
            }
        }
        if (delay_before_stop && !stop_called) sleep(delay_before_stop);
        if (!stop_called) tp.Stop();
    }
    catch(TP_exception& e) {
        std::cout << e.what();
        std::cout << "failed\n";
    }
    std::cout << "\t\t\t";
    if(is_vector_result) {
        Vector res(result);
        if(res == v_result)
            std::cout << "passed\n";
        else {
            std::cout << "Real vect: ";
            res.printIt();
            std::cout << "failed!!!\n";
        }
    }
    else {
        Set res(result);
        if (res == s_result)
            std::cout << "passed\n";
        else {
            std::cout << "Real set: ";
            res.printIt();
            std::cout << "failed!!!\n";
        }
    }
}

void Test::print_conditions() {
    std::cout << "Test# " << test_number << ":\n";
    std::cout << std::string(test_name) << "\n";
    std::cout << "Expected result: " << std::string(test_expected) << "\n";
    if(stop_after > 0)
        std::cout << "Stop after " << stop_after << "th tast runs\n";

    std::cout << "Tasks: \n";
    for(size_t i = 0; i < tasks_array.size(); i++) {
        std::cout << "\t task#" << i << " ";
        tasks_array[i].printIt();
    }

    std::cout << "Workers amount = " << workers_amount << "\n";
    std::cout << "Delay before stop = " << delay_before_stop << "\n";
    if(!s_result.empty()) {
        std::cout << "Result set (Tasks run unordered list): ";
        s_result.printIt();
    }
    else{
        std::cout << "Result array (Tasks run ordered list): ";
        v_result.printIt();
    }
    std::cout << "\n";
}

TestArray::TestArray(const std::string& fname): is_valid(false), ts(NULL) {
    ts = cj_parse(fname.c_str());
    if(!ts) return;

   is_valid = true;

   for(int i = 0; i < cJSON_GetArraySize(ts); i++) {
       Test t(cJSON_GetArrayItem(ts, i), i);
       if(!t.valid()) {
           is_valid = false;
           return;
       }
       push_back(t);
   }
}


