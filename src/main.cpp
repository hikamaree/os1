#include "../h/memory.h"
#include "../h/console.h"
#include "../h/tcb.h"
#include "../h/syscall_c.h"
#include "../h/riscv.h"

extern void userMain();

int main() {
	MEM::init();
	CON::init();
	TCB::init();
	thread_t t;
	thread_create(&t, (void(*)(void*))userMain, nullptr);
	while(!t->isFinished()) {
		thread_dispatch();
	}
	thread_dispatch();
	Riscv::shutdown();
	return 0;
}
