#ifndef BUFFER_H
#define BUFFER_H

#include "../h/semaphore.h"
#include "../h/list.h"

class ConsoleBuffer{
	List<char> buffer;
	SEM* closed;
	SEM* opened;
	SEM* mutex1;
	SEM* mutex2;
	public:
	ConsoleBuffer(uint32 size);
	char get();
	void put(char c);
};

#endif
