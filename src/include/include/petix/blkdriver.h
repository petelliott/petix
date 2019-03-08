#ifndef PETIX_BLKDRIVER_H
#define PETIX_BLKDRIVER_H

struct blkdriver {
    void *extra;
    int (*read_block)(unsigned int block, void *extra, char *loc);
    int (*write_block)(unsigned int block, void *extra, const char *loc);
    void (*wait)(void *extra);
};

int driver_read_block(const struct blkdriver *driver, unsigned int block, char *loc);
int driver_write_block(const struct blkdriver *driver, unsigned int block, const char *loc);
void driver_wait(const struct blkdriver *driver);

#endif
