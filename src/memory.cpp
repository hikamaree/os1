#include "../h/memory.h"

#define ABS(x) ((x < 0) ? (-x) : (x))

int MEM::mem_size = 0;
uint64 MEM::mem_start = 0;
int* MEM::mem_map = 0;

void MEM::init() {
	mem_size = ((uint64)HEAP_END_ADDR - (uint64)HEAP_START_ADDR) / MEM_BLOCK_SIZE;
	mem_start = ((uint64)HEAP_START_ADDR + mem_size * sizeof(int));
	mem_map = (int*)HEAP_START_ADDR;
	for (int i = 1; i < mem_size; i++)
		mem_map[i] = 0;
	mem_map[0] = mem_size;
}

void* MEM::malloc(int size, bool syscall) {
	if(!syscall) {
		size = size / MEM_BLOCK_SIZE + ((size % MEM_BLOCK_SIZE != 0) ? 1 : 0);
	}
	if (size <= 0 || size > mem_size) return 0;
	for (int i = 0; i < mem_size; i += ABS(mem_map[i])) {
		if (mem_map[i] >= size) {
			if (mem_map[i] > size) {
				mem_map[i + size] = mem_map[i] - size;
			}
			mem_map[i] = -size;
			return (void *)(mem_start + MEM_BLOCK_SIZE * i);
		}
	}
	return 0;
}

int MEM::free(void *p) {
	uint64 ptr = (uint64)p;
	if (ptr == 0 || ptr < (uint64)mem_start || ptr >= (uint64)HEAP_END_ADDR) return -1;
	uint32 id = (ptr - (uint64)mem_start) / MEM_BLOCK_SIZE;
	if (mem_map[id] >= 0) return -2;
	mem_map[id] = ABS(mem_map[id]);
	for (int i = 0; i < mem_size; i += ABS(mem_map[i])) {
        if (mem_map[i] > 0 && mem_map[i + mem_map[i]] > 0) {
			int id = i + mem_map[i];
			if(id > mem_size) break;
            mem_map[i] += mem_map[id];
            mem_map[id] = 0;
        }
    }
	return 0;
}
