#include <iostream>

#include "tests_set.hpp"

test_t test_set[TESTS_AMOUNT] = {
        Test1_0,
        Test2_0,
        Test3_0,
        Test3_1,
        Test4,
        Test4_1,
        Test5,
        Test6,
        Test6_1,
        Test6_2
};

int main() {

    try {
        for (int i = 0; i < 1; i++) {
            test_set[i]();
        }
    }
    catch(TE& e) {
        std::cerr << "ThreadPool test set failed on " << e.what() << std::endl;
        return -1;
    }

    return 0;
}
