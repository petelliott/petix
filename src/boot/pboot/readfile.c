#include "readfile.h"
#include <petix/fs.h>
#include <petix/debug.h>

#define PETIX_LIBC_FREESTANDING
#include <string.h>


void open_driver(const char *name, int dnum, struct blkdriver *driver);

static unsigned int currblock = 0;
static char blkbuff[BLOCK_SIZE];

static void get_inode(const struct blkdriver *driver, unsigned int inum, struct inode *inode) {
    unsigned int block = 3 + inum/(BLOCK_SIZE/sizeof(struct inode));
    int off = inum % (BLOCK_SIZE/sizeof(struct inode));

    if (block != currblock) {
        driver_read_block(driver, block, blkbuff);
        driver_wait(driver);
        currblock = block;
    }

    memcpy(inode, (struct inode *)(blkbuff) + off, sizeof(struct inode *));
}

static unsigned int one_level_dir(const struct blkdriver *driver, const char *name, const struct inode *inode) {
    kassert(inode->flags & INODE_DIRECTORY);
    kassert(!(inode->flags & INODE_LARGE));

    for (int i = 0; i < inode->size/sizeof(struct dentry); ++i) {
        unsigned int block = inode->blocks[i/(BLOCK_SIZE/sizeof(struct dentry))];
        int off = i%(BLOCK_SIZE/sizeof(struct dentry));

        if (block != currblock) {
            driver_read_block(driver, block, blkbuff);
            driver_wait(driver);
            currblock = block;
        }

        struct dentry *dentry = ((struct dentry *)blkbuff) + off;

        if (strncmp(dentry->name, name, sizeof(dentry->name)) == 0) {
            return dentry->inode;
        }
    }

    panic("file not found in directory");
    return 0;
}

static unsigned int get_block_n(const struct blkdriver *driver, const struct inode *inode, unsigned int n) {
    kassert(n < inode->size * BLOCK_SIZE);
    unsigned int trueblock;
    if (inode->flags & INODE_LARGE) {
        kassert(n < 8*256);
        unsigned int ind_block = inode->blocks[n/256];
        kassert(ind_block != 0);
        unsigned int off = n%(BLOCK_SIZE/sizeof(unsigned int));

        if (ind_block != currblock) {
            driver_read_block(driver, ind_block, blkbuff);
            driver_wait(driver);
            currblock = ind_block;
        }

        trueblock = ((unsigned int *) currblock)[off];
    } else {
        kassert(n < 8);
        trueblock = inode->blocks[n];
    }

    kassert(trueblock != 0);
    return trueblock;
}

/* reads a file from the root directory of the filesystem on driver */
int readfile(const struct blkdriver *driver, const char *path, char *loc) {
    struct inode inode;
    get_inode(driver, 0, &inode);

    //TODO: support non root boot files.
    unsigned int inum = one_level_dir(driver, path, &inode);
    get_inode(driver, inum, &inode);

    for (int i = 0; i < inode.size; ++i) {
        unsigned int blockn = get_block_n(driver, &inode, i);
        driver_read_block(driver, blockn, loc + i*BLOCK_SIZE);
        driver_wait(driver);
    }

    return 0;
}
