#include "disk.h"

static inline int dn_equal(const char *d1, const char *d2) {
    return (d1[0] == d2[0]) && (d1[1] == d2[1]);
}

int (*get_read_handler(const char *disk_name))(int, int, int, int *) {
    if (dn_equal(disk_name, "rk")) {
        return &read_rk;
    } else {
        return NULL;
    }
}

static int *const RKER = (int *) 0177402;
static int *const RKCS = (int *) 0177404;
static int *const RKWC = (int *) 0177406;
static int *const RKBA = (int *) 0177410;
static int *const RKDA = (int *) 0177412;

int read_rk(int drivenum, int sector, int nwords, int *off) {
    *RKDA = (drivenum << 13) | sector;
    *RKBA = (int) off;
    *RKWC = nwords;
    *RKCS = 05; // READ + GO

    while (!(*RKCS & 07)) {}
    return *RKER;
}
