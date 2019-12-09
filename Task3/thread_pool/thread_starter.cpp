/*
 Created by gsg on 10/12/2019.
*/

#include "thread_starter.hpp"

ThreadStarter::ThreadStarter(Task& t, Sync& _syn): task(t), syn(_syn), vacant(true)  {}

bool ThreadStarter::run() throw (TP_exception) {
    bool ret;
    if(pthread_attr_init(&attr)) throw TP_exception("ThreadStarter::ThreadStarter: pthread_attr_init error. Abort.");
    if (ret = (pthread_create(&id, &attr, &ThreadStarter::thread_proc, (void*)this)==0), ret) {
        vacant.set(false);
    }
    return ret;
}

void* ThreadStarter::thread_proc(void *param) {
    ThreadStarter *starter = reinterpret_cast<ThreadStarter*>(param);
    starter->task._do();

    void *ret;
    pthread_join(starter->id, &ret);
    pthread_attr_destroy(&starter->attr);


    starter->syn.Notify(Sync::SYN_THREAD_STOPS);
    starter->vacant.set(true);
}
