#include "term.h"
#include <petix/drivers/DL11-W.h>

void write_term_ch(char ch) {
    driver_write_char(&DL11W_driver, ch);
}

char read_term_ch(void) {
    return driver_read_char(&DL11W_driver);
}

char read_echo_ch(void) {
    char ch = read_term_ch();
    write_term_ch(ch);
    return ch;
}

int read_line(char *lb, int len) {
    int off = 0;

    while (1) {
        char ch = read_echo_ch();

        if (ch == '\r') {
            write_term_ch('\n');
            break;
        } else if (ch == '\b') {
            if (off > 0) {
                --off;
            }
        } else if (ch == 0177) {
            if (off > 0) {
                write_str("\b \b");
                --off;
            }
        } else if (off+1 < len) {
            lb[off] = ch;
            ++off;
        }
    }

    lb[off] = '\0';
    return off+1;
}

void keyboard_test(void) {
    while (1) {
        unsigned char ch = read_term_ch();

        write_term_ch(((ch & 0700) >> 6) + '0');
        write_term_ch(((ch & 0070) >> 3) + '0');
        write_term_ch((ch & 0007) + '0');
        write_term_ch('\r');
        write_term_ch('\n');
    }
}

void write_str(const char *str) {
    while (*str != '\0') {
        write_term_ch(*str);
        ++str;
    }
}
