#include "../h/sleep.h"
#include "../h/scheduler.h"
#include "../h/semaphore.h"

Sleep::Node *Sleep::head = nullptr;

void Sleep::put_to_sleep(TCB *thread, time_t time) {
    if (head == nullptr) {
        head = new Node(thread, time, head);
        return;
	}
	if(head->time > time) {
		head->time -= time;
        head = new Node(thread, time, head);
        return;
	}
	Node* curr;
	time -= head->time;
    for (curr = head; curr->next && curr->next->time < time; curr = curr->next) {
        time -= curr->next->time;
    }
    curr->next = new Node(thread, time, curr->next);
	if(curr->next->next != nullptr){
		curr->next->next->time -= curr->next->time;
	}
}

void Sleep::remove_from_sleep(TCB* tcb) {
	if(head == nullptr || tcb == nullptr) return;
	Node* curr = head;
	if(head->tcb == tcb) {
		head = head->next;	
		delete curr;
		return;
	}
	if(head->tcb == tcb) {
		if(head->next != nullptr) {
			head->next->time += head->time;
		}
		head=head->next;
		delete curr;
		return;
	}
	while(curr->next != nullptr && curr->next->tcb != tcb) {
		curr = curr->next;
	}
	if(curr->next == nullptr) return;
	Node* tmp = curr->next;
	curr->next = curr->next->next;
	if(curr->next) {
		curr->next->time += tmp->time;
	}
	delete tmp;
}

void Sleep::trap() {
	if (!head) return;
	head->time--;
	while (head != nullptr && head->time == 0) {
		Node *old = head;
		head = head->next;
		TCB *t = old->tcb;
		delete old;
		if (t && !t->run) {
			t->run = true;
			Scheduler::put(t);
		}
	}
}

int Sleep::time_sleep(time_t time) {
	if(TCB::running == nullptr || time <= 0) return -1;
	TCB::running->run = false;
	put_to_sleep(TCB::running, time);
	TCB::dispatch();
	return 0;
}
