#ifndef A_OUT_H
#define A_OUT_H

/* Code indicating object file or impure executable.  */
#define OMAGIC 0407
/* Code indicating pure executable.  */
#define NMAGIC 0410
/* Code indicating demand-paged executable.  */
#define ZMAGIC 0413
/* This indicates a demand-paged executable with the header in the text.
   The first page is unmapped to help trap NULL pointer references */
#define QMAGIC 0314

/* a.out header */
struct exec {
    unsigned int  a_magic;		/* magic number */
    unsigned int  a_text;		/* size of text segment */
    unsigned int  a_data;		/* size of initialised data */
    unsigned int  a_bss;	    /* size of uinitialised bss */
    unsigned int  a_syms;		/* size of symbol table */
    unsigned int  a_entry;		/* entry point */
    unsigned int  a_unused;		/* unused */
    unsigned int  a_flag;		/* relocation info stripped */
};

//TODO: this is not needed yet.
/*
struct nlist {
  union {
    char *n_name;
    struct nlist *n_next;
    long n_strx;
  } n_un;
  unsigned char n_type;
  char n_other;
  short n_desc;
  unsigned long n_value;
};
*/

#endif
