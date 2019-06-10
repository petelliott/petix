#include <petix/fsctl.h>

int fs_load_sb(struct fs_handle *fs) {
    driver_read_block(&(fs->driver), 1, fs->superblock_data);
    driver_read_block(&(fs->driver), 2, fs->superblock_data+BLOCK_SIZE);

    fs->sb.header = (struct superblock_h *) fs->superblock_data;

    if (fs->sb.header->magic != FS_MAGIC) {
        return -1;
    }

    fs->sb.bmap_bytes = (unsigned int *)(fs->superblock_data + sizeof(fs->sb.header));
    fs->sb.bmap = (char *) (fs->sb.bmap_bytes + 1);
    fs->sb.imap_bytes = (unsigned int *)((char *)fs->sb.bmap + *(fs->sb.bmap_bytes));
    fs->sb.imap = (char *) (fs->sb.imap_bytes + 1);

    return 0;
}

void fs_flush_sb(const struct fs_handle *fs) {
    driver_write_block(&(fs->driver), 1, fs->superblock_data);
    driver_write_block(&(fs->driver), 2, fs->superblock_data+BLOCK_SIZE);
}
