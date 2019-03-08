#ifndef PETIX_DRIVERS_RK11_H
#define PETIX_DRIVERS_RK11_H

#include <petix/blkdriver.h>

#define RKDS ((int *) 01777400)
#define RKER ((int *) 01777402)
#define RKCS ((int *) 01777404)
#define RKWC ((int *) 01777406)
#define RKBA ((int *) 01777410)
#define RKDA ((int *) 01777412)
#define RKMR ((int *) 01777414)
#define RKDB ((int *) 01777416)

int open_RK11(struct blkdriver *driver, int drivenum);

unsigned int RK11_make_RKDA(unsigned int sector, int drivenum);

void RK11_wait(void *extra);

int RK11_read_block(unsigned int block, void *extra, char *loc);
int RK11_write_block(unsigned int block, void *extra, const char *loc);


#endif
