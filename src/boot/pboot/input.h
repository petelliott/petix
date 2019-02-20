#ifndef PBOOT_INPUT_H
#define PBOOT_INPUT_H

enum pboot_cmd_type {
    HALT,
    BOOT,
    HW_TEST,
    HW_DETECT,
    HELP
};

struct pboot_boot {
    char disktype[2];
    int  diskn;
    char *bootf;
};

struct pboot_cmd {
    enum pboot_cmd_type ctype;
    union {
        struct pboot_boot boot;
    } cmd_data;
};

int read_cmd(char *str, struct pboot_cmd *cmd);

int read_cmd_type(char **str, enum pboot_cmd_type *ctype);

int read_pboot_boot(char **str, struct pboot_boot *boot);


#endif
