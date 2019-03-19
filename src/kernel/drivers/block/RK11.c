#include <petix/drivers/RK11.h>
#include <petix/fs.h>


int open_RK11(struct blkdriver *driver, int drivenum) {
    driver->extra = (void *) drivenum;
    driver->read_block = RK11_read_block;
    driver->write_block = RK11_write_block;
    driver->wait = RK11_wait;
    //TODO check if drive exists
    return 0;
}

/* calculates the RKDA register for a given sector, and drive number */
unsigned int RK11_make_RKDA(unsigned int sector, int drivenum) {
    unsigned int lsector = sector % 012;
    sector /= 012;
    unsigned int surface = (sector % 02);
    unsigned int track = (sector / 02);

    return (drivenum << 13)
        | (track << 5)
        | (surface << 4)
        | lsector;
}

void RK11_wait(void *extra) {
    while (*RKCS & (1<<7)) {}
}

int RK11_read_block(unsigned int block, void *extra, char *loc) {
    *RKDA = RK11_make_RKDA(block, (int) extra);
    *RKBA = (unsigned int) loc;
    *RKWC = -BLOCK_SIZE/2;
    *RKCS = 05;
    return 0;
}

int RK11_write_block(unsigned int block, void *extra, const char *loc) {
    *RKDA = RK11_make_RKDA(block, (int) extra);
    *RKBA = (unsigned int) loc;
    *RKWC = -BLOCK_SIZE/2;
    *RKCS = 03;
    return 0;
}
