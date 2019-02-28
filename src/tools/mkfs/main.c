#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include "fs.h"
#include "mkfs.h"
#include <string.h>


int main(int argc, char **argv) {
    if (argc < 5) {
        fprintf(stderr, "useage: %s [dir] [disk] [nblocks] [ninodes]\n", argv[0]);
        return 1;
    }

    uint16_t nblocks = atoi(argv[3]);
    uint16_t ninodes = atoi(argv[4]);

    int fd = open(argv[2], O_RDWR | O_CREAT, 0666);
    if (fd < 0) {
       perror("open()");
       return 1;
    }
    if (ftruncate(fd, nblocks*BLOCK_SIZE) < 0) {
        perror("ftruncate()");
        return 1;
    }

    char *dev = mmap(NULL, nblocks*BLOCK_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    struct superblock sb;
    mk_superblock(dev, &sb, nblocks, ninodes);

    uint16_t d1 = mkdir(&sb, dev);
    uint16_t f1 = mkfile(&sb, dev);

    insert_to_dir(&sb, dev, d1, "testfile", f1);
    const char data[] = "hello worlddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddfddd\n";
    append_to_file(&sb, dev, f1, data, sizeof(data)-1);
    append_to_file(&sb, dev, f1, data, sizeof(data)-1);
    append_to_file(&sb, dev, f1, data, sizeof(data)-1);

    munmap(dev, nblocks*BLOCK_SIZE);
    close(fd);

    return 0;
}
