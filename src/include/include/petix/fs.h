#ifndef PETIX_FS_H
#define PETIX_FS_H

#define BLOCK_SIZE 512

#define FS_MAGIC 030216

struct superblock_h {
    unsigned int magic;
    unsigned int nspecial;
    unsigned int nblocks;
    unsigned int ninodes;
};

struct inode {
    int flags;
    unsigned char nlinks;
    unsigned char uid;
    unsigned int size;
    unsigned int blocks[8];
    unsigned int unused;
    unsigned long creat_time;
    unsigned long mod_time;
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

#define FIRST_INODE     040 // this means nothing until we make device files.

struct dentry {
    unsigned int inode;
    char name[14];
};

#endif
