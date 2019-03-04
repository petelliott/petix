#ifndef PETIX_CHARDRIVER_H
#define PETIX_CHARDRIVER_H

struct chardriver {
    void *extra;
    char (*read_char)(void *extra);
    int (*write_char)(void *extra, char ch);
};

char driver_read_char(const struct chardriver *driver);
int driver_write_char(const struct chardriver *driver, char ch);

#endif
