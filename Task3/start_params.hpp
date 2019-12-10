/*
 Created by gsg on 10/12/2019.
*/

#ifndef TASK3_START_PARAMS_HPP
#define TASK3_START_PARAMS_HPP

#include <ctime>

typedef struct {
    int amt;
    time_t seconds;
} pair_t;

typedef struct {
    pair_t hi;
    pair_t norm;
    pair_t lo;
    int workers_amt;
    time_t delay_before_stop;
    bool valid;
} t_prog_params;

t_prog_params get_program_params(int argc, char *argv[]);
void print_params(const t_prog_params& par);


#endif //TASK3_START_PARAMS_HPP
