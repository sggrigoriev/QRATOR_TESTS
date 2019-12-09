/*
 Created by gsg on 10/12/2019.
*/

#include "manager.hpp"

void Manager::_do() {
    while(true) {
        Task::priority_t p;
        switch (syn.Wait()) {
            case Sync::SYN_THREAD_STOPS:
                if(!q.empty()) {
                    wrk.runTask(q.get());
                }
                break;
            case Sync::SYN_NEW_TASK:
                if(wrk.vacant()) {
                    wrk.runTask(q.get());
                }
                break;
            case Sync::SYN_TOTAL_STOP:
            default:
                return;
        }
    }
}
