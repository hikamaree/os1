#include "../h/syscall_c.h"
#include "../h/riscv.h"

void* mem_alloc(size_t size) {
	size = size / MEM_BLOCK_SIZE + ((size % MEM_BLOCK_SIZE != 0) ? 1 : 0);
	Riscv::syscall(0x01, size);
	return (void*)Riscv::syscall_return();
}

int mem_free(void* p) {
	Riscv::syscall(0x02, p);
	return (int)Riscv::syscall_return();
}

int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg) {
	Riscv::syscall(0x11, handle, start_routine, arg);
	return (int)Riscv::syscall_return();
}

int thread_exit() {
	Riscv::syscall(0x12);
	return (int)Riscv::syscall_return();
}

void thread_dispatch() {
	Riscv::syscall(0x13);
}

int getThreadId() {
	Riscv::syscall(0x14);
	return (int)Riscv::syscall_return();
}

void thread_join(thread_t* handle) {
	Riscv::syscall(0x15, handle);
}

void thread_joinall() {
	Riscv::syscall(0x16);
}

int thread_joinalltime(time_t time) {
	Riscv::syscall(0x17, time);
	return (int)Riscv::syscall_return();
}

int sem_open (sem_t* handle, unsigned init){
	Riscv::syscall(0x21, handle, init);
	return (int)Riscv::syscall_return();
}

int sem_close (sem_t handle){
	Riscv::syscall(0x22, handle);
	return (int)Riscv::syscall_return();
}

int sem_wait (sem_t id){
	Riscv::syscall(0x23, id);
	return (int)Riscv::syscall_return();
}

int sem_signal (sem_t id){
	Riscv::syscall(0x24, id);
	return (int)Riscv::syscall_return();
}

int sem_timedwait(sem_t id, time_t timeout){
	Riscv::syscall(0x25, id, timeout);
	return (int)Riscv::syscall_return();
}

int sem_trywait(sem_t id) {
	Riscv::syscall(0x26, id);
	return (int)Riscv::syscall_return();
}

int time_sleep (time_t time){
	Riscv::syscall(0x31, time);
	return (int)Riscv::syscall_return();
}

char getc (){
	Riscv::syscall(0x41);
	return (char)Riscv::syscall_return();
}

void putc(char c){
	Riscv::syscall(0x42, c);
}
