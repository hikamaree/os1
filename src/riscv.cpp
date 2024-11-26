#include "../h/riscv.h"
#include "../h/tcb.h"
#include "../h/sleep.h"
#include "../h/memory.h"
#include "../h/semaphore.h"
#include "../h/console.h"
#include "../h/stdio.h"

bool Riscv::mode = false;

void Riscv::popSppSpie() {
	__asm__ volatile("csrw sepc, ra");
	mc_sstatus(Riscv::SSTATUS_SPP);
	__asm__ volatile("sret");
}

void Riscv::handleSupervisorTrap() {
	Riscv::mode = false;
	uint64 scause = r_scause();
	uint64 volatile sepc = r_sepc();
	uint64 volatile sstatus = r_sstatus();
	if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL) {
		uint64 code, a1, a2, a3;
		__asm__ volatile ("mv %0, a0" : "=r"(code));
		__asm__ volatile("ld %0, 88(s0)" : "=r" (a1));
		__asm__ volatile("ld %0, 96(s0)" : "=r" (a2));
		__asm__ volatile("ld %0, 104(s0)" : "=r" (a3));
		switch (code) {
			case 0x01:
				syscall_exec((uint64)MEM::malloc(a1, true));
				break;
			case 0x02:
				syscall_exec(MEM::free((void*)a1));
				break;
			case 0x11:
				*(TCB**)a1 = TCB::createThread((void(*)(void*))a2, (void*)a3);
				syscall_exec((*(TCB**)a1 != nullptr) ? 0 : -1);
				break;
			case 0x12:
				TCB::thread_exit();
				syscall_exec(0);
				break;
			case 0x13:
				TCB::dispatch();
				break;
			case 0x14:
				syscall_exec(TCB::running->id);
				break;
			case 0x15:
				TCB::running->join((TCB**)a1);
				break;
			case 0x16:
				TCB::running->joinAll();
				break;
			case 0x17:
				syscall_exec(TCB::running->joinAllTime((time_t)a1));
				break;
			case 0x21:
				*(SEM**)a1 = SEM::open(a2);
				syscall_exec((*(SEM**)a1 != nullptr) ? 0 : -1);
				break;
			case 0x22:
				syscall_exec(SEM::close((SEM*)a1));
				break;
			case 0x23:
				syscall_exec(((SEM*)a1)->wait());
				break;
			case 0x24:
				syscall_exec(((SEM*)a1)->signal());
				break;
			case 0x25:
				syscall_exec(((SEM*)a1)->timedWait((time_t)a2));
				break;
			case 0x26:
				syscall_exec(((SEM*)a1)->tryWait());
				break;
			case 0x31:
				syscall_exec(Sleep::time_sleep((time_t)a1));
				break;
			case 0x41:
				syscall_exec(CON::get_input());
				break;
			case 0x42:
				CON::put_output((char)a1);
				break;
		}
		w_sstatus(sstatus);
		w_sepc(sepc + 4);
	} else if (scause == 0x8000000000000001UL) {
		mc_sip(SIP_SSIP);
		Sleep::trap();
		TCB::timeSliceCounter++;
		if (TCB::timeSliceCounter >= TCB::running->getTimeSlice()) {
			TCB::dispatch();
		}
		w_sstatus(sstatus);
		w_sepc(sepc);
	} else if (scause == 0x8000000000000009UL) {
		uint64 cnt = plic_claim();
		if (cnt == CONSOLE_IRQ) {
			while (CONSOLE_RX_STATUS_BIT & (*(char *) CONSOLE_STATUS)) {
				CON::put_input(*(char *) CONSOLE_RX_DATA);
			}
		}
		plic_complete((int)cnt);
		w_sstatus(sstatus);
		w_sepc(sepc);
	} else {
		__printf("Scause: %d\n", scause);
		__printf("Sepc: %x\n", sepc);
		TCB::thread_exit();
	}
	Riscv::mode = true;
}
