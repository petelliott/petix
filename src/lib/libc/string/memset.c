#include <string.h>


void *memset(void *str, int c, size_t n) {
    char *cstr = (char *) str;

    for (size_t i = 0; i < n; ++i) {
        cstr[i] = c;
    }

    return str;
}
