#include <petix/drivers/DL11-W.h>

const struct chardriver DL11W_driver = {
    .extra = NULL,
    .read_char = DL11W_read_char,
    .write_char = DL11W_write_char
};

char DL11W_read_char(void *extra) {
    while (!(*RCSR & 1<<7)) {}
    return *RBUF & 0377;
}

int DL11W_write_char(void *extra, char ch) {
    while (!(*XCSR & 1<<7)) {}
    *XBUF = ch;
    return 0;
}
