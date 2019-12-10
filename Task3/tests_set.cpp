/*
 Created by gsg on 09/12/2019.
*/



#include <unistd.h>
#include <iostream>

#include "task.hpp"
#include "thread_pool.hpp"

#include "tests_set.hpp"

class AxB: public Task {
public:
    AxB(int op1, int op2): a(op1), b(op2), c(0) {}
    int getResult() { return c; }
    virtual void _do() { c = a*b; }
private:
    int a,b,c;
};

class SlowAnswer: public Task {
public:
    explicit SlowAnswer(time_t sec_interval) { delay = sec_interval; }
    virtual void _do() { sleep(delay); std::cout << "SlowAnswer after " << delay << " seconds\n";}
private:
    time_t delay;

};


void Test1_0() { // "Task test: calc smth inside, get result", 10
    std::string str = std::string(__FUNCTION__) + std::string(": calc smth inside, get result");

    AxB ab(2,2);
    ThreadPool tp(1);
    tp.Enqueue(ab, Task::norm);
//    sleep(1);
    tp.Stop();
    if(ab.getResult() == 4)
        std::cout << str << " " << "OK\n";
    else {
        throw TE(__FUNCTION__);
    }
}
void Test2_0() { //"Task test: delay N seconds, print result", 20
    std::string str = std::string(__FUNCTION__) + std::string(": delay N seconds, print result");
//
    throw TE(__FUNCTION__);
}

void Test3_0() { //"Low task does not start until there is higher priority in queue", 3
    std::string str = std::string(__FUNCTION__) + std::string(": ow task does not start until there is higher priority in queue");
//
    throw TE(__FUNCTION__);
}
void Test3_1() { //"Low task runs if no hi and norm are in queue and there are free workers", 31
    std::string str = std::string(__FUNCTION__) + std::string(": Low task runs if no hi and norm are in queue and there are free workers");
//
    throw TE(__FUNCTION__);
}

void Test4() { //"Normal task runs after 3 hi tasks", 4
    std::string str = std::string(__FUNCTION__) + std::string(": Normal task runs after 3 hi tasks");
//
    throw TE(__FUNCTION__);
}
void Test4_1() {//"Normal task runs if no hi tasks in queue", 51
    std::string str = std::string(__FUNCTION__) + std::string(": Normal task runs if no hi tasks in queue");
//
    throw TE(__FUNCTION__);
}
void Test5() { // "No new tasks run after Stop() call", 6
    std::string str = std::string(__FUNCTION__) + std::string(": No new tasks run after Stop() call");
//
    throw TE(__FUNCTION__);
}
void Test6() { //Stack errors on Task 6
    std::string str = std::string(__FUNCTION__) + std::string(": Stack error on Task");
//
    throw TE(__FUNCTION__);
}
void Test6_1() { //Dynamic memory error on Task 61
    std::string str = std::string(__FUNCTION__) + std::string(": Dynamic memory error on Task");
//
    throw TE(__FUNCTION__);
}
void Test6_2() {// Divizion by 0 on Task 62
    std::string str = std::string(__FUNCTION__) + std::string(": Divizion by 0 on Task");
//
    throw TE(__FUNCTION__);

}

