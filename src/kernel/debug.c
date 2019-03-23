#include <petix/debug.h>
#include <petix/drivers/DL11-W.h>
#include <stdarg.h>


void kputc(char ch) {
    if (ch == '\n') {
        driver_write_char(&DL11W_driver, '\r');
    }
    driver_write_char(&DL11W_driver, ch);
}

void kputs(const char *str) {
    for (const char *ch = str; *ch != 0; ++ch) {
        kputc(*ch);
    }
}


static void putuintnz(unsigned long int num) {
    if (num != 0) {
        putuintnz(num/10);
        kputc((num % 10) + '0');
    }
}

static void putuint(unsigned long int num) {
    if (num == 0) {
        kputc('0');
    } else {
        putuintnz(num);
    }
}


static void putint(int num) {
    if (num < 0) {
        kputc('-');
        putuint(-num);
    } else {
        putuint(num);
    }
}

void kprintf(const char *fmt, ...) {
    va_list ap;
	va_start(ap, fmt);

    for (const char *ch = fmt; *ch != 0; ++ch) {
        if (*ch == '%') {
            ++ch;
            if (*ch == 0) {
                break;
            }
            switch (*ch) {
                case '%':
                    kputc(*ch);
                    break;
                case 'd':
                case 'i':
                    putint(va_arg(ap, int));
                    break;
                case 'u':
                    putuint(va_arg(ap, unsigned int));
                    break;
                case 's':
                    kputs(va_arg(ap, const char *));
                    break;
                case 'c':
                    kputc(va_arg(ap, int));
            }
        } else {
            kputc(*ch);
        }
    }
    va_end(ap);
}

void kassert_internal(int tst, int line, const char *file, const char *tststr) {
    if (!tst) {
        kprintf("kassertion failed (%s:%i): %s\n", file, line, tststr);
        asm("HALT");
    }
}

void panic_internal(const char *str, int line, const char *file) {
    kprintf("kernel panic (%s:%i): %s\n", file, line, str);
    asm("HALT");
}
