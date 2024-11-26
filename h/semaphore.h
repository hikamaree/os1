#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "../h/list.h"
#include "../lib/hw.h"

class TCB;
class SEM {
	List<TCB> blocked;
	volatile int count;
	bool opened;
	public:
	SEM(unsigned init = 1) : count(init), opened(true) {}
	virtual ~SEM() {}
	static SEM* open(unsigned init);
	static int close(SEM* sem);
	int wait();
	int signal(bool print = false);
	int timedWait(time_t);
	int tryWait();
};

#endif
