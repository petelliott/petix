#include <string.h>

static void byte_cpy(char *dest, const char *src, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        dest[i] = src[i];
    }
}

void *memcpy(void *dest, const void *src, size_t n) {

    size_t align = ((size_t) dest) % sizeof(size_t);
    byte_cpy(dest, src, align);

    n -= align;

    size_t *sdest = (size_t *) ((char *)dest + align);
    const size_t *ssrc = (const size_t *) ((const char *)src + align);

    size_t i;
    for (i = 0; i < n/sizeof(size_t); ++i) {
        sdest[i] = ssrc[i];
    }
    n -= sizeof(size_t) * i;

    byte_cpy((char *) (sdest + i), (const char *) (ssrc + i), n);

    return dest;
}
