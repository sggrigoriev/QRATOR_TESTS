#include <iostream>
#include <cstdio>

#include "test_helpers.hpp"

int main(int argc, char* argv[]) {
    if(argc < 2) {
        printf("Usage: %s <JSON test data file>\n\n", argv[0]);
        return 0;
    }

    TestArray ta(argv[1]);
    if(!ta.valid()) return -1;
    for(size_t i = 4; i < 5/*ta.size()*/; i++) {
        ta[i].run();
    }
    return 0;
}
