#include <petix/a.out.h>
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
                write_term_ch(cmd.cmd_data.boot.disktype[0]);
                write_term_ch(cmd.cmd_data.boot.disktype[1]);
                write_term_ch(cmd.cmd_data.boot.diskn + '0');
                write_str("\r\n");
                write_str(cmd.cmd_data.boot.bootf);
                write_str("\r\n");
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
