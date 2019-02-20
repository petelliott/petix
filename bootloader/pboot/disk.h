#ifndef PBOOT_DISK_H
#define PBOOT_DISK_H

#define NULL ((void *) 0177777)

int (*get_read_handler(const char *disk_name))(int, int, int, int *);

int read_rk(int drivenum, int sector, int nwords, int *off);

#endif
