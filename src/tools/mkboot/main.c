#include "sectors.h"
#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include <fs.h>
#include <string.h>
#include <assert.h>
#include "rdfs.h"
#include "sectors.h"

#define CEIL(x,y) (((x) + (y) - 1) / (y))

void copy_bs(char *dev, const char *spec);

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "useage: %s [disk] [image] [path]\n", argv[0]);
        return 1;
    }

    int fd = open(argv[2], O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
       perror("open()");
       return 1;
    }

    off_t fsize = lseek(fd, 0, SEEK_END);

    char *dev = mmap(NULL, fsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    copy_bs(dev, argv[1]);

    uint16_t inode =  get_in_path(dev, argv[3], 0);
    struct inode *in = get_inode(dev, inode);

    int nblocks = CEIL(in->size, BLOCK_SIZE);
    assert(nblocks < 16);

    for (int i = 0; i < nblocks; ++i) {
        uint16_t block = get_block_n(dev, in, i);
        assert(block != 0);

        printf("%u\n", block);
    }

    munmap(dev, fsize);
    close(fd);

    return 0;
}

void copy_bs(char *dev, const char *spec) {
    if (spec[0] == 'r' && spec[1] == 'k') {
        memcpy(dev, rkbs, sizeof(rkbs));
    } else {
        fprintf(stderr, "unsupported drive spec\n");
    }
}
