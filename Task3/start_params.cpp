/*
 Created by gsg on 10/12/2019.
*/

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "start_params.hpp"



typedef enum {No_type, HiParm, NormParm, LoParm, WorkersAmt, DelaySec} par_types;

par_types get_type(const char* token) {
    if(!token) return No_type;
    if(strcmp(token, "-h") == 0) return HiParm;
    if(strcmp(token, "-n") == 0) return NormParm;
    if(strcmp(token, "-l") == 0) return LoParm;
    if(strcmp(token, "-w") == 0) return WorkersAmt;
    if(strcmp(token, "-d") == 0) return DelaySec;
    return No_type;
}
static pair_t get_pair(const char* str) {
    pair_t ret;
    if(sscanf(str, "%d,%ld", &ret.amt, &ret.seconds) != 2) {
        ret.amt = 0;
        ret.seconds = 0;
    }
    return ret;
}
t_prog_params get_program_params(int argc, char *argv[]) {
    t_prog_params ret = {0};
    ret.valid = true;
    par_types context = get_type(argv[1]);
    for(int i = 2; i < argc; i++) {
        if(get_type(argv[i]) != No_type)
            context = get_type(argv[i]);
        else  // context is No_type - we got parameter!
            switch (context) {
                case HiParm:
                    ret.hi = get_pair(argv[i]);
                    break;
                case NormParm:
                    ret.norm = get_pair(argv[i]);
                    break;
                case LoParm:
                    ret.lo = get_pair(argv[i]);
                    break;
                case WorkersAmt:
                    ret.workers_amt = (int)strtoul(argv[i], NULL, 0);
                    break;
                case DelaySec:
                    ret.delay_before_stop = strtoul(argv[i], NULL, 0);
                    break;
                default:
                    ret.valid = false;
                    break;
            }
    }
    return ret;
}

void print_params(const t_prog_params& par) {
    if(!par.valid) {
        std::cout << "Invalid parameters\n";
        return;
    }
    std::cout << "Input parameters:\n";
    if(par.hi.amt) std::cout << "High priority tasks\t" << par.hi.amt << " run time = " << par.hi.seconds << "\n";
    if(par.norm.amt) std::cout << "Norm priority tasks\t" << par.norm.amt << " run time = " << par.norm.seconds << "\n";
    if(par.lo.amt) std::cout << "Low priority tasks\t" << par.lo.amt << " run time = " << par.lo.seconds << "\n";
    std::cout << "Workers amount\t" << par.workers_amt << "\n";
    std::cout << "Delay before stop\t" << par.delay_before_stop << "\n";
}