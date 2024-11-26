# OS1

This is a simple operating system developed as a university project. The system is designed to run on RISC-V architecture and implements basic functionalities, including memory management, threading, semaphores, and basic I/O.

## System Calls

### Memory Management
- `void* mem_alloc(size_t size);`
  Allocates memory of size `size` and returns a pointer to the beginning of the allocated memory.
- `int mem_free(void*);`
  Frees previously allocated memory.

### Thread Management
- `int thread_create(thread_t* handle, void(*start_routine)(void*), void* arg);`
  Creates a new thread that executes the function `start_routine` with the argument `arg`.
- `void thread_dispatch();`
  Manually switches context to another thread.
- `int thread_exit();`
  Ends the current thread.
- `int getThreadId();`
  Returns the ID of the current thread.
- `void thread_join(thread_t* handle);`
  Waits for the specified thread to finish.
- `void thread_joinall();`
  Waits for all threads to finish.
- `int thread_joinalltime(time_t time);`
  Waits for all threads to finish, but no longer than the specified time `time`.

### Semaphores
- `int sem_open(sem_t* handle, unsigned init);`
  Initializes a semaphore with the initial value `init`.
- `int sem_close(sem_t handle);`
  Frees resources associated with the semaphore.
- `int sem_wait(sem_t id);`
  Decrements the semaphore value and blocks if the value is 0.
- `int sem_signal(sem_t id);`
  Increments the semaphore value.
- `int sem_timedwait(sem_t id, time_t timeout);`
  Waits for the semaphore with a timeout.
- `int sem_trywait(sem_t id);`
  Attempts to decrement the semaphore value without blocking.

### Time Management
- `int time_sleep(time_t);`
  Pauses thread execution for the specified time.

### Input/Output
- `char getc();`
  Reads a single character from standard input.
- `void putc(char);`
  Writes a single character to standard output.

