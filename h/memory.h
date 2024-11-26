#ifndef MEMORY_H
#define MEMORY_H

#include "../lib/hw.h"

class MEM {
	public:
		static void init();
		static void* malloc(int size, bool syscall = false);
		static int free(void* ptr);
	private:
		static int mem_size;
		static uint64 mem_start;
		static int* mem_map;
};

#endif
