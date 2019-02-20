#include <a.out.h>
#include "term.h"
#include "disk.h"

void _start(void) {
    write_str("example: xx(n, n)\r\n"
              "where xx is the disk type (one of rk,)\r\n"
              "(n, n) is the disk number and sector offset\r\n"
              "> ");
    while (1) {
        write_term_ch(read_term_ch());
    }
}
