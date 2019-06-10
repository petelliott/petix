#include <petix/fsctl.h>

#define PETIX_LIBC_FREESTANDING
#include <string.h>

static unsigned int first_free(char b) {
    for (int i = 0; i < 8; ++i) {
        if (((b>>i) &1) == 0) {
            return i;
        }
    }
    return 0;
}

unsigned int fs_allocate_block(struct fs_handle *fs) {
    for (unsigned int i = 0; i < *(fs->sb.bmap_bytes); ++i) {
        if (fs->sb.bmap[i] < 0xffu) {
            unsigned int ffree = first_free(fs->sb.bmap[i]);
            fs->sb.bmap[i] |= (1 << ffree);
            return i*8 + ffree;
        }
    }
    return 0;
}

unsigned int fs_allocate_inode(struct fs_handle *fs) {
    for (unsigned int i = 0; i < *(fs->sb.imap_bytes); ++i) {
        if (fs->sb.imap[i] < 0xffu) {
            unsigned int ffree = first_free(fs->sb.imap[i]);
            fs->sb.imap[i] |= (1 << ffree);
            return i*8 + ffree;
        }
    }
    return 0;
}

void fs_get_inode(const struct fs_handle *fs, unsigned int inum,
        struct inode *inode) {

    char buff[BLOCK_SIZE];
    driver_read_block(&(fs->driver),
            inum/(BLOCK_SIZE/sizeof(struct inode)), buff);

    memcpy(inode, buff+(inum % (BLOCK_SIZE/sizeof(struct inode))),
            sizeof(struct inode));
}

unsigned int fs_mkdir(struct fs_handle *fs);
unsigned int fs_touch(struct fs_handle *fs);
