#include <petix/chardriver.h>

char driver_read_char(const struct chardriver *driver) {
    return (*(driver->read_char))(driver->extra);
}


int driver_write_char(const struct chardriver *driver, char ch) {
    return (*(driver->write_char))(driver->extra, ch);
}
