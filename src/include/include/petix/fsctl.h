#ifndef PETIX_FSCTL_H
#define PETIX_FSCTL_H

#include <petix/fs.h>
#include <petix/blkdriver.h>

struct superblock {
    struct superblock_h *header;
    unsigned int *bmap_bytes;
    char *bmap;
    unsigned int *imap_bytes;
    char *imap;
};

struct fs_handle {
    char superblock_data[BLOCK_SIZE * 2];
    struct superblock sb;
    struct blkdriver driver;
};

int fs_load_sb(struct fs_handle *fs);
void fs_flush_sb(const struct fs_handle *fs);

unsigned int fs_allocate_block(struct fs_handle *fs);
unsigned int fs_allocate_inode(struct fs_handle *fs);

void fs_get_inode(const struct fs_handle *fs, unsigned int inum, struct inode *inode);

unsigned int fs_mkdir(struct fs_handle *fs);
unsigned int fs_touch(struct fs_handle *fs);

void fs_upgrade_to_large(struct fs_handle *fs, unsigned int inum);
void fs_resize_file(struct fs_handle *fs, unsigned int inum, int delta);

void fs_dir_insert(struct fs_handle *fs, unsigned int dinode, const char *name, unsigned int inum);
void fs_write(struct fs_handle *fs, unsigned int off, const char *data, unsigned int len);
void fs_read(struct fs_handle *fs, unsigned int off, char *data, unsigned int len);

unsigned int fs_lookup(struct fs_handle *fs, const char *path);
unsigned int fs_unlink(struct fs_handle *fs, const char *path);

#endif
