#ifndef SYSCALL_CPP_H__
#define SYSCALL_CPP_H__

#include "syscall_c.h"

class Thread {
	public:
		Thread(void (*body)(void *), void *arg) : body(body), arg(arg) {}
		virtual ~Thread () { delete myHandle; }
		int start ();
		static void dispatch ();
		static int sleep (time_t);
		int getThreadId();
		void join();
	protected:
		Thread() : body(Thread::Run), arg(this) {}
		virtual void run () {}
	private:
		static void Run(void* thread);
		thread_t myHandle;
		void (*body)(void*);
		void* arg;
};

class Semaphore {
	public:
		Semaphore (unsigned init = 1) { sem_open(&myHandle, init); }
		virtual ~Semaphore ();
		int wait ();
		int signal ();
		int timedWait (time_t);
		int tryWait();
	private:
		sem_t myHandle;
};

class PeriodicThread : public Thread {
	public:
		void terminate ();
	protected:
		PeriodicThread (time_t period): period(period) {}
		virtual void periodicActivation () {}
	private:
		void run();
		time_t period;
};

class Console {
	public:
		static char getc ();
		static void putc (char);
};

#endif
