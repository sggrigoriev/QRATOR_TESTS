/*
 Created by gsg on 10/12/2019.
*/

#include <cassert>

#include "workers.hpp"

void Workers::runTask(Task& t) throw(TP_exception) {
    assert(vacant());

    TaskStarter* ts = new  TaskStarter(t, syn);
    ts->run();
    running.push_back(ts);
}
/**
 * Find all vacant threads,
 * finish'em and pop oup from running queue
 * If mode == CLEAN_ALL -> wait for all tasks finish
 * TODO: direct deletion by index
 * TODO: zombies for CLEAN_ALL mode
 */
void Workers::cleanClearing(clean_t mode) {
    ts_list_t::iterator it=running.begin();
    while(it != running.end()) {
        if((*it)->isVacant() || (mode == CLEAN_ALL)) {
            (*it)->stop();
            delete (*it);
            it = running.erase(it);
        }
        else {
            ++it;
        }
    }
}
