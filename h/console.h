#ifndef CONSOLE_H
#define CONSOLE_H

#include "../h/buffer.h"

class CON {
	static ConsoleBuffer* input;
	static ConsoleBuffer* output;
	public:
	static char get_input();
	static char get_output();
	static void put_input(char c);
	static void put_output(char c);
	static void init();
	static void print();
};

#endif
