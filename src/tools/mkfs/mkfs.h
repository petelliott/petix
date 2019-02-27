#ifndef MKFS
#define MKFS

#include "fs.h"

void mk_superblock(char *dev, struct superblock *sb, int nblocks, int ninodes);

uint16_t allocate_block(struct superblock *sb);
uint16_t allocate_inode(struct superblock *sb);

struct inode *get_inode(char *dev, uint16_t inum);

uint16_t mkdir(struct superblock *sb, char *dev);
uint16_t mkfile(struct superblock *sb, char *dev);

void copy_to_file(char *dev, uint16_t inode, const void *data, uint16_t n);
void insert_to_dir(char *dev, uint16_t dinode, const char *name, uint16_t inode);

#endif
