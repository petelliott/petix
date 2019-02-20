#include "term.h"

static int *const printer_data   = (int *) 0177566;
static int *const printer_status = (int *) 0177564;

void write_term_ch(char ch) {
    while (!(*printer_status & 1<<7)) {}
    *printer_data = ch;
}

static int *const reader_data   = (int *) 0177562;
static int *const reader_status = (int *) 0177560;

char read_term_ch(void) {
    while (!(*reader_status & 1<<7)) {}
    return *reader_data & 0377;
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
