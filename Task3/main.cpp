#include <iostream>

#include "tests_set.hpp"
#include "start_params.hpp"

test_t test_set[TESTS_AMOUNT] = {
        Test1_0,
        Test2_0,
        Test3_0,
        Test3_1,
        Test4,
        Test4_1,
        Test5,
};

const std::string usage =
        "Qrator Task-3 test bed\n"
        "Parameters:\n"
        " -h <N1,N2>                            N1: High priority tasks amount, N2 - work time in seconds each\n"
        " -n <N1,N2>                            N1: Normal priority tasks amount, N2 - work time in seconds each\n"
        " -l <N1,N2>                            N1: Low priority tasks amount, N2 - work time in seconds each\n"
        " -w <N>                                Workers amount\n"
        " -d <N>                                Delay in seconds before ThreadPool::Stop() call\n"
        ;

int main(int argc, char *argv[]) {
    if(argc < 2) {
        try {
            for (int i = 0; i < TESTS_AMOUNT; i++) {
                test_set[i]();
            }
        }
        catch (TE &e) {
            std::cerr << "ThreadPool test set failed on " << e.what() << std::endl;
            return -1;
        }
    }
//Run with parameters
    t_prog_params PARAMETERS = get_program_params(argc, argv);
    print_params(PARAMETERS);

    if(!PARAMETERS.valid) {
        std::cout << usage << "\n";
        return 0;
    }

    TestHand(PARAMETERS);

    return 0;
}
