#include <iostream>
#include <cstdio>
#include <thread_pool.hpp>

#include "test_helpers.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: %s <JSON test data file>\n\n", argv[0]);
        return 0;
    }

    TestArray ta(argv[1]);
    if(!ta.valid()) return -1;
    for(size_t i = 0; i < ta.size(); i++) {
        ta[i].run();
    }
    ThreadPool* tp = new ThreadPool(100);
    delete tp;
    return 0;
}
