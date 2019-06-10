#ifndef PBOOT_BOOT_H
#define PBOOT_BOOT_H

#include <petix/a.out.h>

void boot(struct exec *header, void *stack);

#endif
