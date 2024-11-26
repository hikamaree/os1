#include "../h/syscall_cpp.hpp"
#include "../h/syscall_c.h"

void Thread::Run(void* thread) {
	((Thread*)thread)->run();
}

int Thread::start() {
	return thread_create(&this->myHandle, this->body, this->arg);
}

void Thread::dispatch(){
	thread_dispatch();
}

int Thread::sleep(time_t time) {
	return time_sleep(time);
}

int Thread::getThreadId() {
	return ::getThreadId();
}

void Thread::join() {
	thread_join(&myHandle);
}

Semaphore::~Semaphore(){
	sem_close(this->myHandle);
}

int Semaphore::wait() {
	return sem_wait(this->myHandle);
}

int Semaphore::signal() {
	return sem_signal(this->myHandle);
}

int Semaphore::timedWait(time_t time) {
	return sem_timedwait(this->myHandle, time);
}

int Semaphore::tryWait() {
	return sem_trywait(this->myHandle);
}

void PeriodicThread::terminate() {
    this->period = -1;
}

void PeriodicThread::run() {
    while (this->period > 0) {
        Thread::sleep(period);
        this->periodicActivation();
    }
}

char Console::getc() {
	return ::getc();
}

void Console::putc(char c) {
	::putc(c);
}
