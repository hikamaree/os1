#ifndef SYSCALL_H
#define SYSCALL_H

#include "../lib/hw.h"
#include "../h/tcb.h"
#include "../h/semaphore.h"

typedef TCB* thread_t;
typedef SEM* sem_t;
static const int EOF = -1;
void* mem_alloc(size_t size);
int mem_free(void *);
int thread_create (thread_t* handle, void(*start_routine)(void*), void* arg);
void thread_dispatch();
int thread_exit();
int getThreadId();
void thread_join(thread_t* handle);
void thread_joinall();
int thread_joinalltime(time_t time);
int sem_open (sem_t* handle, unsigned init);
int sem_close (sem_t handle);
int sem_wait (sem_t id);
int sem_signal (sem_t id);
int sem_timedwait(sem_t id, time_t timeout);
int sem_trywait(sem_t id);
int time_sleep (time_t);
char getc ();
void putc (char);
#endif
