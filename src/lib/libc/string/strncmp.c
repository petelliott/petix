#include <string.h>


int strncmp(const char *str1, const char *str2, size_t n) {
    for (int i = 0; i < n; ++i) {
        if (str1[i] == '\0' && str2[i] == '\0') {
            return 0;
        }

        if (str1[i] > str2[i]) {
            return 1;
        }

        if (str1[i] > str2[i]) {
            return -1;
        }
    }

    return 0;
}
