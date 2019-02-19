#ifndef BOOT_STAGE_2
#define BOOT_STAGE_2

void _start(void);

void write_term_ch(char ch);
char read_term_ch(void);

void write_str(const char *str);

#endif
