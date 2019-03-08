#include <petix/blkdriver.h>

int driver_read_block(const struct blkdriver *driver, unsigned int block, char *loc) {
    return (*(driver->read_block))(block, driver->extra, loc);
}

int driver_write_block(const struct blkdriver *driver, unsigned int block, const char *loc) {
    return (*(driver->write_block))(block, driver->extra, loc);
}

void driver_wait(const struct blkdriver *driver) {
    (*(driver->wait))(driver->extra);
}
