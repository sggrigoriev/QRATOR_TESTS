/*
 Created by gsg on 09/12/2019.
*/



#include <unistd.h>
#include <iostream>
#include <cstdio>

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
    SlowAnswer(time_t sec_interval, const std::string& str): delay(sec_interval), s(str) {}
    void setName(const std::string& name) {s = name;}
    void setDelay(time_t sec) {delay = sec;}
    virtual void _do() {
        sleep(delay);
        std::cout << "\n" << s << "\n";
    }
private:
    time_t delay;
    std::string s;
};


void Test1_0() { // "Task test: calc smth inside, get result", 10
    std::string str = std::string(__FUNCTION__) + std::string(": calc smth inside, get result");

    AxB ab(2,2);
    ThreadPool tp(1);
    tp.Enqueue(ab, Task::norm);

    tp.Stop();

    if(ab.getResult() == 4)
        std::cout << str << " " << "OK\n";
    else {
        throw TE(__FUNCTION__);
    }
}
void Test2_0() { //"Tthe task can't start if no available workers
    std::cout << std::string(__FUNCTION__) + std::string(": the task can't start if no available workers\n");

    SlowAnswer sa(3, "Task1 run!");
    SlowAnswer qa(1, "Task2 run!");

    ThreadPool tp(1);
    std::cout <<"\nThreadPool started with 1 worker\n";

    tp.Enqueue(sa, Task::lo);
    std::cout << "Task1 with low priority added\n";

    tp.Enqueue(qa, Task::lo);
    std::cout << "Task2 with low priority added\n";

    tp.Stop();

    std::cout << "\n- good if Task1 run and Task2 - not \n\n";
}

void Test3_0() { //"Low task does not start until there is higher priority in queue", 3
    std::cout << std::string(__FUNCTION__) + std::string(": low priority task does not start until there is higher priority in queue");

    SlowAnswer t1(2, "Task1 run!");
    SlowAnswer t2(2, "Task2 run!");
    SlowAnswer t3(2, "Task3 run!");
    SlowAnswer t4(1, "Task4 run!");

    ThreadPool tp(1);
    std::cout << "\nThreadPool started with 1 worker\n";

    tp.Enqueue(t1, Task::hi);
    std::cout << "Task1 with hi priority added\n";
    tp.Enqueue(t2, Task::hi);
    std::cout << "Task2 with hi priority added\n";
    tp.Enqueue(t3, Task::hi);
    std::cout << "Task3 with hi priority added\n";
    tp.Enqueue(t4, Task::lo);
    std::cout << "Task4 with lo priority added\n";
sleep(5);
    tp.Stop();

    std::cout << "\n- good if Task1, Task2, Task3 run and Task4 not\n\n";
}
void Test3_1() { //"Low task runs if no hi and norm are in queue and there are free workers", 31
    std::cout << std::string(__FUNCTION__) + std::string(": Low task runs if no hi and norm are in queue and there are free workers\n");

    SlowAnswer t1(2, "Task1 run!");
    SlowAnswer t2(2, "Task2 run!");
    SlowAnswer t3(2, "Task3 run!");
    SlowAnswer t4(1, "Task4 run!");

    ThreadPool tp(1);
    std::cout << "ThreadPool started with 1 worker\n";

    tp.Enqueue(t1, Task::norm);
    std::cout << "Task1 with norm priority added\n";
    tp.Enqueue(t2, Task::hi);
    std::cout << "Task2 with hi priority added\n";
    tp.Enqueue(t3, Task::hi);
    std::cout << "Task3 with hi priority added\n";
    tp.Enqueue(t4, Task::lo);
    std::cout << "Task4 with lo priority added\n";

    sleep(7);
    tp.Stop();

    std::cout << "\n- good if Task2, Task3, Task1 run and Task4 run after'em\n\n";
}

void Test4() { //"Normal task runs after 3 hi tasks"
    std::cout << std::string(__FUNCTION__) + std::string(": Normal task runs after 3 hi tasks\n");
    SlowAnswer t1(1, "Task1 run!");
    SlowAnswer t2(1, "Task2 run!");
    SlowAnswer t3(1, "Task3 run!");
    SlowAnswer t4(1, "Task4 run!");
    SlowAnswer t5(1, "Task5 run!");

    ThreadPool tp(2);
    std::cout << "\nThreadPool started with 1 workers\n";

    tp.Enqueue(t1, Task::hi);
    std::cout << "Task1 with hi priority added\n";
    tp.Enqueue(t2, Task::norm);
    std::cout << "Task2 with norm priority added\n";
    tp.Enqueue(t3, Task::hi);
    std::cout << "Task3 with hi priority added\n";
    tp.Enqueue(t4, Task::hi);
    std::cout << "Task4 with hi priority added\n";
    tp.Enqueue(t5, Task::hi);
    std::cout << "Task5 with hi priority added\n";

    sleep(3);
    tp.Stop();

    std::cout << "\n- good if Tasks 1,3,4(hi) run, Task1(norm) run, Task5(hi) run in this order\n\n";
}
void Test4_1() {//"Normal task runs if no hi tasks in queue", 51
    std::cout << std::string(__FUNCTION__) + std::string(": Normal task runs if no hi tasks in queue\n");

    SlowAnswer t1(1, "Task1 run!");
    SlowAnswer t2(1, "Task2 run!");
    SlowAnswer t3(1, "Task3 run!");
    SlowAnswer t4(1, "Task4 run!");
    SlowAnswer t5(1, "Task5 run!");

    ThreadPool tp(2);
    std::cout << "\nThreadPool started with 2 workers\n";

    tp.Enqueue(t1, Task::norm);
    std::cout << "Task1 with norm priority added\n";
    tp.Enqueue(t2, Task::hi);
    std::cout << "Task2 with hi priority added\n";
    tp.Enqueue(t3, Task::hi);
    std::cout << "Task3 with hi priority added\n";

    sleep(2);
    tp.Stop();

    std::cout << "\n- good if Tasks 2,3(hi) run, Task1(norm) run in this order\n\n";
}
void Test5() { // "No new tasks run after Stop() call", 6
    std::cout << std::string(__FUNCTION__) + std::string(": No new tasks run after Stop() call\n");

    SlowAnswer t1(1, "Task1 run!");
    SlowAnswer t2(1, "Task2 run!");

    ThreadPool tp(2);
    std::cout << "\nThreadPool started with 2 workers\n";

    tp.Enqueue(t1, Task::norm);
    std::cout << "Task1 with norm priority added\n";
    tp.Stop();
    std::cout << "Stop() run\n";
    bool no_way = tp.Enqueue(t2, Task::hi);
    if(no_way) {
        std::cout << "Task2 with hi priority was not added after Stop() call - Ok\n";
    }
    else {
        throw TE(__FUNCTION__);
    }
}

void createSA(std::vector<SlowAnswer>& v, pair_t& par, const std::string& name) {
    char buf[30];
    snprintf(buf, sizeof(buf), "%ld", par.seconds);
    for(int i = 0; i < par.amt; i++) {
        SlowAnswer sa(par.seconds, name+std::string(buf)+std::string(" run"));
        v.push_back(sa);
    }
}
void runSA(ThreadPool& tp, std::vector<SlowAnswer>& sa, Task::priority_t p) {
    for(int i = 0; i < sa.size(); i++) {
        tp.Enqueue(sa[i], p);
    }
}

void TestHand(t_prog_params params) {
    std::vector<SlowAnswer> hi;
    std::vector<SlowAnswer> norm;
    std::vector<SlowAnswer> lo;

    createSA(hi, params.hi, "High Task");
    createSA(norm, params.norm, "Norm Task");
    createSA(lo, params.lo, "Low Task");

    ThreadPool tp(params.workers_amt);

    runSA(tp, hi, Task::hi);
    runSA(tp, norm, Task::norm);
    runSA(tp, lo, Task::lo);

    if(params.delay_before_stop > 0) sleep(params.delay_before_stop);

    tp.Stop();
}

