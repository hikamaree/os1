#include "../h/memory.h"
#include "../h/riscv.h"
#include "../h/syscall_c.h"

using size_t = decltype(sizeof(0));

void *operator new(size_t n) {
    return Riscv::mode ? mem_alloc(n) : MEM::malloc(n);
}

void *operator new[](size_t n) {
    return Riscv::mode ? mem_alloc(n) : MEM::malloc(n);
}

void operator delete(void *p) noexcept {
    Riscv::mode ? mem_free(p) : MEM::free(p);
}

void operator delete[](void *p) noexcept {
    Riscv::mode ? mem_free(p) : MEM::free(p);
}
