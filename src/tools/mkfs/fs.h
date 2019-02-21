#ifndef PETIX_FS_H
#define PETIX_FS_H

#include <stdint.h>

#define BLOCK_SIZE 512

#define FS_MAGIC 030216

struct superblock_h {
    uint16_t magic;
    uint16_t n_special;
    uint16_t nblocks;
    uint16_t ninodes;
};

struct superblock {
    struct superblock_h *header;
    uint16_t *bmap_bytes;
    char *bmap;
    uint16_t *imap_bytes;
    char *imap;
};

struct inode {
    uint16_t flags;
    uint8_t nlinks;
    uint8_t uid;
    uint16_t size;
    uint16_t blocks[8];
    uint16_t unused;
    uint32_t creat_time;
    uint32_t mod_time;
};

#define INODE_ALLOCATED 0100000
#define INODE_DIRECTORY 0040000
#define INODE_MODIFIED  0020000
#define INODE_LARGE     0010000
#define INODE_SETUID    0000040
#define INODE_EXECUTE   0000020
#define INODE_R_OWNER   0000010
#define INODE_W_OWNER   0000004
#define INODE_R_OTHER   0000002
#define INODE_W_OTHER   0000001

#define FIRST_INODE     040

struct dentry_row {
    uint16_t inode;
    char name[14];
};

#endif
