#include "input.h"

#define skip_wspace(str) while (*(str) == ' ') { ++(str); }

int read_cmd(char *str, struct pboot_cmd *cmd) {
    skip_wspace(str);
    if (!read_cmd_type(&str, &(cmd->ctype))) {
        return 0;
    }
    skip_wspace(str);

    switch (cmd->ctype) {
        case BOOT:
            if (!read_pboot_boot(&str, &(cmd->cmd_data.boot))) {
                return 0;
            }
            break;
        case HALT:
        case HW_TEST:
        case HW_DETECT:
        case HELP:
            break;
        default:
            return 0;
    }

    return 1;

}

static int tok_equal(char **strm, const char *tok) {
    char *save = *strm;
    while (**strm >= 'A' && **strm <= 'z') {
        if (*(tok++) != **strm) {
            *strm = save;
            return 0;
        }
        ++(*strm);
    }
    return 1;
}

int read_cmd_type(char **str, enum pboot_cmd_type *ctype) {

    if (tok_equal(str, "boot")) {
        *ctype = BOOT;
    } else if (tok_equal(str, "halt")) {
        *ctype = HALT;
    } else if (tok_equal(str, "help")) {
        *ctype = HELP;
    } else {
        return 0;
    }

    return 1;
}

int read_pboot_boot(char **str, struct pboot_boot *boot) {
    if ((*str)[0] > 'z' || (*str)[0] < 'a' || (*str)[1] > 'z' ||
            (*str)[1] < 'a' || (*str)[2] > '9' || (*str)[2] < '0') {
        return 0;
    }
    boot->disktype[0] = (*str)[0];
    boot->disktype[1] = (*str)[1];
    boot->diskn = (*str)[2] - '0';

    skip_wspace(*str);

    boot->bootf = *str;
    return 1;
}
