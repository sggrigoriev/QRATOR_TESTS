/*
 Created by gsg on 10/12/2019.
*/

#include <cassert>
#include <cstring>
#include "sync.hpp"

Sync::Sync() {
    pthread_mutex_init(&s_mutex, NULL);
    pthread_cond_init (&signal, NULL);

    pthread_mutex_init(&ec_mutex, NULL);
    memset(events_counter, 0, sizeof(sync_event_t)*SYN_SIZE);
}
Sync::~Sync() {
    pthread_mutex_destroy(&s_mutex);
    pthread_cond_destroy(&signal);
    pthread_mutex_destroy(&ec_mutex);
}

void Sync::Notify(sync_event_t e) {
    assert((e >= SYN_THREAD_STOPS) && (e < SYN_SIZE));
    pthread_mutex_lock(&s_mutex);
        pthread_mutex_lock(&ec_mutex);
            events_counter[e]++;
        pthread_mutex_unlock(&ec_mutex);
        pthread_cond_signal(&signal);
    pthread_mutex_unlock(&s_mutex);
}
Sync::sync_event_t Sync::Wait() {
    sync_event_t event;

    pthread_mutex_lock(&s_mutex);
        event = getEvent();
        while (event == SYN_SIZE) {
            pthread_cond_wait(&signal, &s_mutex);
            event = getEvent();
        }
    pthread_mutex_unlock(&s_mutex);
    return event;
}

Sync::sync_event_t Sync::getEvent() {
    sync_event_t ret;
    pthread_mutex_lock(&ec_mutex);
    for(int i = SYN_THREAD_STOPS; i < SYN_SIZE; i++) {
        if(events_counter[i]) {
            ret = static_cast<sync_event_t>(i);
            events_counter[i]--;
            pthread_mutex_unlock(&ec_mutex);
            return ret;
        }
    }
    pthread_mutex_unlock(&ec_mutex);
    return SYN_SIZE;
}