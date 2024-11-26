#include "../h/scheduler.h"

List<TCB> Scheduler::readyThreadQueue;

TCB *Scheduler::get() {
    return readyThreadQueue.removeFirst();
}

void Scheduler::put(TCB *ccb) {
    readyThreadQueue.addLast(ccb);
}
