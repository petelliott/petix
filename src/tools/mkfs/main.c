#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>
#include "fs.h"
#include "mkfs.h"
#include <string.h>
#include <dirent.h>

uint16_t walkdir(const char *name, struct superblock *sb, char *dev);

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

    /*
    uint16_t d1 = mkdir(&sb, dev);
    uint16_t f1 = mkfile(&sb, dev);

    insert_to_dir(&sb, dev, d1, "testfile", f1);
    const char data[] = "hello worlddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddddfddd\n";

    for (int i = 0; i < 16; ++i) {
        append_to_file(&sb, dev, f1, data, sizeof(data)-1);
        append_to_file(&sb, dev, f1, data, sizeof(data)-1);
        append_to_file(&sb, dev, f1, data, sizeof(data)-1);
    }
    */
    walkdir(argv[1], &sb, dev);

    munmap(dev, nblocks*BLOCK_SIZE);
    close(fd);

    return 0;
}

uint16_t readfile(const char *name, struct superblock *sb, char *dev) {
    uint16_t inode = mkfile(sb, dev);
    char buff[BLOCK_SIZE];

    int fd = open(name, O_RDONLY);

    ssize_t n;
    while (1) {
        n = read(fd, buff, sizeof(buff));
        if (n <= 0) {
            break;
        }
        append_to_file(sb, dev, inode, buff, n);
    }

    close(fd);

    return inode;
}

uint16_t walkdir(const char *name, struct superblock *sb, char *dev) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(name))) {
        abort();
    }

    uint16_t inode = mkdir(sb, dev);

    while ((entry = readdir(dir)) != NULL) {
        char path[1024];
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;
        snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
        if (entry->d_type == DT_DIR) {
            printf("%s\n",  entry->d_name);
            insert_to_dir(sb, dev, inode, entry->d_name, walkdir(path, sb, dev));
        } else {
            printf("%s\n", entry->d_name);
            insert_to_dir(sb, dev, inode, entry->d_name, readfile(path, sb, dev));
        }
    }
    closedir(dir);
    return inode;
}
