#include "../h/tcb.h"
#include "../h/riscv.h"

TCB *TCB::running = nullptr;
uint64 TCB::timeSliceCounter = 0;
int TCB::ID = 10;

void TCB::init() {
	TCB::running = TCB::createThread(nullptr, nullptr);
	Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
	Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
}

TCB *TCB::createThread(Body body, void *arg) {
	return new TCB(body, arg);
}

void TCB::yield() {
    __asm__ volatile("li a0, 0x13");
    __asm__ volatile ("ecall");
}

void TCB::dispatch() {
    TCB *old = running;
    if (!old->isFinished() && old->run == true) {
		Scheduler::put(old);
	}
    running = Scheduler::get();
	timeSliceCounter = 0;
    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::threadWrapper() {
    Riscv::popSppSpie();
	running->body(running->arg);
	TCB::thread_exit();
}

void TCB::thread_exit() {
	TCB::running->setFinished(true);
	if(TCB::running->father->body != nullptr) {
		TCB::running->father->child_cnt--;
		if(TCB::running->father->child_cnt == 0) {
			TCB::running->father->joinall_sem->signal();
		}
	}
	while(TCB::running->joined_cnt--) {
		TCB::running->father->join_sem->signal();
	}
	TCB::yield();
}

void TCB::join(TCB** handle) {
	if(!handle || !*handle) return;
	(*handle)->joined_cnt++;
	(*handle)->join_sem->wait();
}

void TCB::joinAll() {
	if(child_cnt > 0) {
		joinall_sem->wait();
	}
}

int TCB::joinAllTime(time_t time) {
	if(child_cnt > 0) {
		return joinall_sem->timedWait(time);
	}
	return 0;
}
