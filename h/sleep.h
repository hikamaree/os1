#ifndef SLEEP_H
#define SLEEP_H

#include "../h/tcb.h"

class Sleep {
	struct Node {
		TCB *tcb;
		time_t time;
		Node *next;
		Node(TCB *tcb, time_t time, Node *next = nullptr) : tcb(tcb), time(time), next(next) {}
	};
	static Node *head;
	static Node *tail;
	public:
	static void put_to_sleep(TCB*, time_t);
	static void remove_from_sleep(TCB* tcb);
	static void trap();
	static int time_sleep(time_t);
};

#endif
