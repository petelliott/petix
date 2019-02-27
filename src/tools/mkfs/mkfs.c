#include "mkfs.h"
#include <string.h>

void mk_superblock(char *dev, struct superblock *sb, int nblocks, int ninodes) {
    sb->header = (void *) dev+BLOCK_SIZE;
    sb->header->magic     = FS_MAGIC;
    sb->header->n_special = 32;
    sb->header->nblocks   = nblocks;
    sb->header->ninodes   = ninodes;

    sb->bmap_bytes = (void *) ((char *)sb->header + sizeof(struct superblock_h));
    *(sb->bmap_bytes) = 2 * (nblocks/16 + 16);
    sb->bmap = ((char *) sb->bmap_bytes) + 2;
    memset(sb->bmap, 0x00, *(sb->bmap_bytes));
    memset(sb->bmap,  0xff, ((ninodes/16)/8) + 1);

    sb->imap_bytes = (void *) ((char *) sb->bmap + *(sb->bmap_bytes));
    *(sb->imap_bytes) = 2 * (ninodes/16 + 16);
    sb->imap = ((char *) sb->imap_bytes) + 2;
    memset(sb->imap, 0x00, *(sb->imap_bytes));
}

static int first_free(char b) {
    for (int i = 0; i < 8; ++i) {
        if (((b>>i) & 1) == 0) {
            return i;
        }
    }
    return 0;
}

uint16_t allocate_block(struct superblock *sb) {
    for (int i = 0; i < *(sb->bmap_bytes); ++i) {
        if (sb->bmap[i] < 0xffu) {
            int ffree = first_free(sb->bmap[i]);
            sb->bmap[i] |= (1 << ffree);
            return 3 + i*8 + ffree;
        }
    }
    return 0;
}

uint16_t allocate_inode(struct superblock *sb) {
    for (int i = 0; i < *(sb->imap_bytes); ++i) {
        if (sb->imap[i] < 0xffu) {
            int ffree = first_free(sb->imap[i]);
            sb->imap[i] |= (1 << ffree);
            return i*8 + ffree;
        }
    }
    return 0xffffu;
}

struct inode *get_inode(char *dev, uint16_t inum) {
    return (struct inode *)(dev + 3*BLOCK_SIZE + 32*inum);
}

uint16_t mkdir(struct superblock *sb, char *dev) {
    uint16_t inum = allocate_inode(sb);
    struct inode *inode = get_inode(dev, inum);
    *inode = (struct inode){
        .flags = INODE_ALLOCATED | INODE_DIRECTORY | INODE_MODIFIED,
        .nlinks = 1,
        .uid = 0,
        .size = 0,
        .blocks = {0},
        .unused = 0,
        .creat_time = 0,
        .mod_time = 0
    };
    return inum;
}

uint16_t mkfile(struct superblock *sb, char *dev);

void copy_to_file(char *dev, uint16_t inode, const void *data, uint16_t n);
void insert_to_dir(char *dev, uint16_t dinode, const char *name, uint16_t inode);
