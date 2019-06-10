#include "boot.h"
#include "term.h"

#define PETIX_LIBC_FREESTANDING
#include <string.h>



/* executes an a.out executable in memory, starting from it's header,
 * with the stack pointer stack
 */
void boot(struct exec *header, void *stack) {
    if (header->a_magic != NMAGIC) {
        write_str("invalid magic number of executable\r\n");
        return;
    }

    char *text_start = (char *)(header+1);
    char *bss_start = text_start + header->a_text + header->a_data;

    // zero bss
    memset(bss_start, 0, header->a_bss);

    void (*bootfun)(void);

    bootfun = (void (*)(void)) header->a_entry;

    // setup the new stack pointer. no going back now
    asm("mov %[stack], SP"
        :
        : [stack] "r" (stack));

    // call the kernel
    (*bootfun)();

    // don't attempt to do anything if the kernel returns.
    asm("halt");
}
