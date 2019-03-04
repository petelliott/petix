#ifndef PETIX_BLKDRIVER_H
#define PETIX_BLKDRIVER_H

struct blkdriver {
    void *extra;
    int (*read_block)(unsigned int block, void *extra, char *loc);
    int (*write_block)(unsigned int block, void *extra, char *loc);
};

int read_block(const struct blkdriver *driver, unsigned int block, char *loc);
int write_block(const struct blkdriver *driver, unsigned int block, char *loc);

#endif
