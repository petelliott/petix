#ifndef PETIX_PANIC_H
#define PETIX_PANIC_H

#include <petix/drivers/DL11-W.h>

#define kassert(tst) kassert_internal((tst), __LINE__, __FILE__, #tst)
#define panic(str) panic_internal((str), __LINE__, __FILE__)

// macros to print that survive all linker issues
#define db_inline_putc(ch) {*XBUF = (ch); while (!(*XCSR & 1<<7)) {}}

void kputc(char ch);
void kputs(const char *str);
void kprintf(const char *fmt, ...);
void kassert_internal(int tst, int line, const char *file, const char *tststr);
void panic_internal(const char *str, int line, const char *file);

#endif
