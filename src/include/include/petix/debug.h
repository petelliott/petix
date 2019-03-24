#ifndef PETIX_PANIC_H
#define PETIX_PANIC_H

#define kassert(tst) kassert_internal((tst), __LINE__, __FILE__, #tst)
#define panic(str) panic_internal((str), __LINE__, __FILE__)

void kputc(char ch);
void kputs(const char *str);
void kprintf(const char *fmt, ...);
void kassert_internal(int tst, int line, const char *file, const char *tststr);
void panic_internal(const char *str, int line, const char *file);

#endif
