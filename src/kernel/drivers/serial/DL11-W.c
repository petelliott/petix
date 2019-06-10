#include <petix/drivers/DL11-W.h>


int open_DL11W(struct chardriver *chardriver) {
    chardriver->extra = NULL;
    chardriver->read_char = &DL11W_read_char;
    chardriver->write_char = &DL11W_write_char;
    return 0;
}

char DL11W_read_char(void *extra) {
    while (!(*RCSR & 1<<7)) {}
    return *RBUF & 0377;
}

int DL11W_write_char(void *extra, char ch) {
    while (!(*XCSR & 1<<7)) {}
    *XBUF = ch;
    return 0;
}
