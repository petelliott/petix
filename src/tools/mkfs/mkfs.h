#ifndef MKFS
#define MKFS

#include <fs.h>

void mk_superblock(char *dev, struct superblock *sb, int nblocks, int ninodes);

uint16_t allocate_block(struct superblock *sb);
uint16_t allocate_inode(struct superblock *sb);

struct inode *get_inode(char *dev, uint16_t inum);

uint16_t mkdir(struct superblock *sb, char *dev);
uint16_t mkfile(struct superblock *sb, char *dev);

void upgrade_to_large(struct superblock *sb, char *dev, uint16_t inode);
char *get_block(char *dev, const struct inode *inode, uint16_t off);
void append_block(struct superblock *sb, char *dev, struct inode *inode, const char *data, uint16_t n);

void append_to_file(struct superblock *sb, char *dev, uint16_t inode, const void *data, int n);
void insert_to_dir(struct superblock *sb, char *dev, uint16_t dinode, const char *name, uint16_t inode);

#endif
