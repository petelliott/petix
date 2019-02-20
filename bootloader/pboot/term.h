#ifndef PBOOT_TERM_H
#define PBOOT_TERM_H

void write_term_ch(char ch);
char read_term_ch(void);

char read_echo_ch(void);

int read_line(char *lb, int len);

void keyboard_test(void);

void write_str(const char *str);

#endif
