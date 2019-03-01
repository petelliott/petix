#include "rdfs.h"
#include <assert.h>
#include <stdlib.h>
#include <string.h>


struct inode *get_inode(const char *dev, uint16_t inum) {
    return (struct inode *)(dev + 3*BLOCK_SIZE) + inum;
}

uint16_t one_level_dir(const char *dev, const char *name, const struct inode *inode) {
    assert(inode->flags & INODE_DIRECTORY);
    assert(!(inode->flags & INODE_LARGE));

    for (int i = 0; i < inode->size/sizeof(struct dentry); ++i) {
        uint16_t block = inode->blocks[i/(BLOCK_SIZE/sizeof(struct dentry))];
        int off = i%(BLOCK_SIZE/sizeof(struct dentry));

        struct dentry *dentry = (struct dentry *)(dev + BLOCK_SIZE*block) + off;

        if (strncmp(dentry->name, name, sizeof(dentry->name)) == 0) {
            return dentry->inode;
        }
    }

    abort();
}

uint16_t get_in_path(const char *dev, char *path, uint16_t root) {
    char *rest;
    char *first = strtok_r(path, "/", &rest);

    if (first == NULL) {
        return root;
    }

    struct inode *inode = get_inode(dev, root);
    uint16_t ninode = one_level_dir(dev, first, inode);
    return get_in_path(dev, rest, ninode);
}

uint16_t get_block_n(const char *dev, const struct inode *inode, uint16_t n) {
    assert(n < inode->size * BLOCK_SIZE);
    uint16_t trueblock;
    if (inode->flags & INODE_LARGE) {
        assert(n < 8*256);
        uint16_t ind_block = inode->blocks[n/256];
        assert(ind_block != 0);
        trueblock = *((uint16_t *)(dev + ind_block*BLOCK_SIZE) + n%256);
    } else {
        assert(n < 8);
        trueblock = inode->blocks[n];
    }

    assert(trueblock != 0);
    return trueblock;
}
