#include <petix/blkdriver.h>

int driver_read_block(const struct blkdriver *driver, unsigned int block, char *loc) {
    driver_wait(driver);
    return (*(driver->read_block))(block, driver->extra, loc);
    driver_wait(driver);
}

int driver_write_block(const struct blkdriver *driver, unsigned int block, const char *loc) {
    driver_wait(driver);
    return (*(driver->write_block))(block, driver->extra, loc);
    driver_wait(driver);
}

void driver_wait(const struct blkdriver *driver) {
    (*(driver->wait))(driver->extra);
}
