#ifndef TCB_H
#define TCB_H

#include "../lib/hw.h"
#include "scheduler.h"
#include "../h/semaphore.h"

class TCB {
public:
    ~TCB() { delete[] stack; }
	static void init();
    bool isFinished() const { return finished; }
    void setFinished(bool value) { finished = value; }
    uint64 getTimeSlice() const { return timeSlice; }
    using Body = void (*)(void*);
    static TCB *createThread(Body body, void* arg);
    static void thread_exit();
    static void dispatch();
    static void yield();
	void join(TCB** handle);
	void joinAll();
	int joinAllTime(time_t time);
	int id;
	bool run;
	bool timer;
    static TCB *running;
private:
    TCB(Body body, void* arg) : id(ID++), run(true), timer(false),
			body(body), arg(arg), stack(body != nullptr ? new uint64[DEFAULT_STACK_SIZE] : nullptr),
            context({(uint64) &threadWrapper, stack != nullptr ? (uint64) &stack[DEFAULT_STACK_SIZE] : 0 }),
			timeSlice(DEFAULT_TIME_SLICE), finished(false), father(TCB::running), child_cnt(0), joined_cnt(0) {
        if (body != nullptr) {
			Scheduler::put(this);
			joinall_sem = SEM::open(0);
			join_sem = SEM::open(0);
			if(father != nullptr) {
				father->child_cnt++;
			}
		}
    }
    struct Context {
        uint64 ra;
        uint64 sp;
    };
    friend class Riscv;
    Body body;
	void* arg;
    uint64 *stack;
    Context context;
    uint64 timeSlice;
    bool finished;
	SEM* joinall_sem;
	SEM* join_sem;
	TCB* father;
	int child_cnt;
	int joined_cnt;
    static void threadWrapper();
    static void contextSwitch(Context *oldContext, Context *runningContext);
    static uint64 timeSliceCounter;
	static int ID;
};

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_TCB_HPP
