#ifndef PBOOT_READFILE_H
#define PBOOT_READFILE_H

#include <petix/blkdriver.h>

int open_driver(const char *name, int dnum, struct blkdriver *driver);

int readfile(const struct blkdriver *driver, const char *path, char *loc);

#endif
