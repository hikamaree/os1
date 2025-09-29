#include "../h/semaphore.h"
#include "../h/sleep.h"

SEM* SEM::open(unsigned init) {
	return new SEM(init);
}

int SEM::close(SEM* sem) {
	if(!sem->opened) return -1;
	while (sem->blocked.peekLast()) {
		TCB* tcb = sem->blocked.removeFirst();
		tcb->run = true;
		if(tcb->timer)
			Sleep::remove_from_sleep(tcb);
		tcb->timer = false;
		Scheduler::put(tcb);
	}
	sem->opened = false;
	return 0;
}

int SEM::wait() {
	if(!opened) return -1;
	count--;
	if (count < 0) {
		blocked.addLast(TCB::running);
		TCB::running->run = false;
		TCB::yield();
	}
	return 0;
}

int SEM::signal() {
	if(!opened) return -1;
	count++;
	if(count <= 0) {
		TCB* tcb = this->blocked.removeFirst();
		if(tcb == nullptr) return 0;
		tcb->run = true;
		if(tcb->timer)
			Sleep::remove_from_sleep(tcb);
		tcb->timer = false;
		Scheduler::put(tcb);
	}
	return 0;
}

int SEM::timedWait(time_t time) {
	if(time <= 0) return -2;
	if(!opened) return -1;
	count--;
	if ((int)count < 0) {
		TCB::running->timer = true;
		TCB::running->run = false;
		Sleep::put_to_sleep(TCB::running, time);
		blocked.addLast(TCB::running);
		TCB::yield();
		if(TCB::running->timer == true) {
			blocked.removeElem(TCB::running);
			count++;
			TCB::running->timer = false;
			return -2;
		}
	}
	return 0;
}

int SEM::tryWait() {
	if (!opened) return -1;
	if (count > 0) {
		count--;
		return 1;
	}
	return 0;
}
