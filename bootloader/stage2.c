#include <a.out.h>
#include "stage2.h"

/* make sure this is located at 00 */
void _start(void) {
    write_str("wecome the bootloader\r\n");
    while (1) {
        write_term_ch(read_term_ch());
    }
}


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

void write_str(const char *str) {
    while (*str != '\0') {
        write_term_ch(*str);
        ++str;
    }
}
