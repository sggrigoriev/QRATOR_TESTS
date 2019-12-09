/*
 Created by gsg on 09/12/2019.
*/

#ifndef TASK3_TESTS_SET_HPP
#define TASK3_TESTS_SET_HPP


#include <stdexcept>


struct TE : std::runtime_error {
    explicit TE(const char* msg) : std::runtime_error(msg) {}
};


void Test1_0(); //Task test: calc smth inside, get result
void Test2_0(); //Task test: delay N seconds, print result", 20

void Test3_0(); //Low task does not start until there is higher priority in queue
void Test3_1(); //Low task runs if no hi and norm are in queue and there are free workers

void Test4(); //Normal task runs after 3 hi tasks
void Test4_1(); //Normal task runs if no hi tasks in queue

void Test5(); //"No new tasks run after Stop() call

void Test6(); //Stack errors on Task 6
void Test6_1(); //Dynamic memory error on Task 61
void Test6_2(); // Divizion by 0 on Task 62

#define TESTS_AMOUNT 10
typedef void(*test_t)();



#endif //TASK3_TESTS_SET_HPP
