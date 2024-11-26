#include "../h/stdio.h"
#include <stdarg.h>

void puts(const void* s) {
	char* str = (char*)s;
	while(*str) {
		putc(*str);
		str++;
	}
}

void puti(long n, int base) {
	const char number[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
	if (n < 0) {
		putc('-');
		n = -n;
	}
	int cnt = 0;
	char buff[32];
	if(n == 0) {
		buff[cnt++] = '0';
	}
	for(; n != 0; n /= base) {
		buff[cnt++] = number [n % base];
	}
	for(int i = cnt - 1; i >= 0; i--) {
		putc(buff[i]);
	}
}

void __printf(const char* fmt, ...) {
	va_list arg;
	va_start(arg, fmt);
	for(; *fmt != '\0'; fmt++) {
		if(*fmt == '%'){
			fmt++;
			switch (*fmt) {
				case '%':
					putc(*fmt);
					break;
				case 'c':
					putc(va_arg(arg, int));
					break;
				case 's':
					puts(va_arg(arg, void *));
					break;
				case 'd':
					puti(va_arg(arg, long), 10);
					break;
				case 'x':
					puti(va_arg(arg, long), 16);
					break;
				default:
					break;
			}
		} else {
			putc(*fmt);
		}
	}
	va_end(arg);
}
