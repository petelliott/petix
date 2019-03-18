#ifndef PETIX_DRIVERS_DL11_W_H
#define PETIX_DRIVERS_DL11_W_H

#include <petix/chardriver.h>
#include <_null.h>


extern const struct chardriver DL11W_driver;

#define XBUF ((int *) 01777566)
#define XCSR ((int *) 01777564)
#define RBUF ((int *) 01777562)
#define RCSR ((int *) 01777560)

char DL11W_read_char(void *extra);
int DL11W_write_char(void *extra, char ch);

#endif
