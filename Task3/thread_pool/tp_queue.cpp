/*
 Created by gsg on 10/12/2019.
*/

#include "tp_queue.hpp"

void TpQueue::add(Task* t, Task::priority_t p) {
    assert((p >= Task::hi) && (p < Task::sz));
    q[p].push(t);
}
Task& TpQueue::get(Task::priority_t p) {
    assert((p >= Task::hi) && (p < Task::sz) && !q[p].empty());
    Task& ret = *q[p].front();
    q[p].pop();
    return ret;
}
bool TpQueue::empty(Task::priority_t p) const {
    assert((p >= Task::hi) && (p < Task::sz));
    return q[p].empty();
}
/*
 Приоритеты обрабатываются следующим образом:
    low-задачи не выполняются никогда, пока в очереди есть хотя бы одна задача с другим приоритетом.
    на 3 high-задачи выполняется 1 normal-задача.
    Данная логика относится только к выборке задачи из очереди, уже запущенные задачи приоритизировать не требуется.

    get Low:    q[Task::hi].empty()&&q[Task::norm].empty()&&!q[Task::lo].empty()
    get Norm:   q[Task::hi].empty()&&!&q[Task::norm].empty() ||
                3 hi взяли полряд && !q[Task::norm].empty()
    getHi:      !q[Task::hi].empty() && !(3 hi взяли полряд && !q[Task::norm].empty())
 */
bool PrtTpQueue::each3rdRule() {
    return (hi_in_a_row >= 3) && !q[Task::norm].empty();
}
bool PrtTpQueue::empty() const  {return TpQueue::empty(Task::hi)&&TpQueue::empty(Task::norm)&&TpQueue::empty(Task::lo);}

Task& PrtTpQueue::get() {
    if(!TpQueue::empty(Task::hi) && !each3rdRule()) {
        hi_in_a_row++;
        return TpQueue::get(Task::hi);
    }
    if((TpQueue::empty(Task::hi) || each3rdRule()) && !TpQueue::empty(Task::norm)) {
        hi_in_a_row = 0;
        return TpQueue::get(Task::norm);
    }
    if(!TpQueue::empty(Task::lo)) {
        hi_in_a_row = 0;
        return TpQueue::get(Task::lo);
    }
}
