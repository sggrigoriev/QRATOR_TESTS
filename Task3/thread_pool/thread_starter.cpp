/*
 Created by gsg on 10/12/2019.
*/

#include "thread_starter.hpp"

bool ThreadStarter::run() throw (TP_exception) {
    if(pthread_attr_init(&attr)) throw TP_exception("ThreadStarter::run: pthread_attr_init error. Abort.");
    return (pthread_create(&id, &attr, &ThreadStarter::thread_proc, (void*)this) == 0);
}

void ThreadStarter::stop() {
    void *ret;
    pthread_join(id, &ret);
    pthread_attr_destroy(&attr);
}

void* ThreadStarter::thread_proc(void *param) {
    ThreadStarter *starter = reinterpret_cast<ThreadStarter*>(param);
    starter->task._do();
    pthread_exit(NULL);
}

/////////////////////////////////////////////////////////

bool TaskStarter::run() throw (TP_exception) {
    if(pthread_attr_init(&attr)) throw TP_exception("TaskStarter::run: pthread_attr_init error. Abort.");
    bool ret = (pthread_create(&id, &attr, &TaskStarter::thread_proc, (void*)this) == 0);

    if(ret) vacant.set(false);
    return ret;
}
void* TaskStarter::thread_proc(void *param) {
    TaskStarter *starter = reinterpret_cast<TaskStarter*>(param);
    starter->task._do();

    starter->vacant.set(true);
    starter->syn.Notify(Sync::SYN_THREAD_STOPS);
    pthread_exit(NULL);
}