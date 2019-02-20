#include <a.out.h>
#include "term.h"
#include "disk.h"
#include "input.h"


void _start(void) {
    while (1) {
        write_str("> ");

        char line[64];
        read_line(line, sizeof(line));

        struct pboot_cmd cmd;
        if (!read_cmd(line, &cmd)) {
            write_str("invalid command.\r\n");
            continue;
        }

        switch (cmd.ctype) {
            case HALT:
                asm("HALT");
                break;
            case BOOT:
                write_str("this is when we should boot\r\n");
                break;
            case HELP:
                write_str("halt\r\n"
                          "boot xxn file (example: boot rk0 unix)\r\n"
                          "help\r\n");
                break;
            default:
                write_str("operation not supported\r\n");
        }
    }

}
