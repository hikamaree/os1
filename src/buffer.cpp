#include "../h/buffer.h"
#include "../h/list.h"

ConsoleBuffer::ConsoleBuffer(uint32 size) {
	closed = SEM::open(0);
	opened = SEM::open(size);
	mutex1 = SEM::open(1);
	mutex2 = SEM::open(1);
}

void ConsoleBuffer::put(char c) {
    opened->wait();
	mutex1->wait();
	buffer.addLast(new char(c));
	mutex1->signal(true);
    closed->signal(true);
}

char ConsoleBuffer::get() {
    closed->wait();
	mutex2->wait();
	char *p = buffer.removeFirst();
	char c = *p;
	delete p;
	mutex2->signal(true);
    opened->signal(true);
    return c;
}
