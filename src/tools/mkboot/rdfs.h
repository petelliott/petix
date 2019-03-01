#ifndef RD_FS
#define RD_FS

#include <fs.h>

struct inode *get_inode(const char *dev, uint16_t inum);

uint16_t one_level_dir(const char *dev, const char *name, const struct inode *inode);

uint16_t get_in_path(const char *dev, char *path, uint16_t root);

uint16_t get_block_n(const char *dev, const struct inode *inode, uint16_t n);

#endif
