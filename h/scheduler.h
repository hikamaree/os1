#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "../h/list.h"

class TCB;
class Scheduler {
	static List<TCB> readyThreadQueue;
	public:
	static TCB *get();
	static void put(TCB *ccb);
};

#endif
