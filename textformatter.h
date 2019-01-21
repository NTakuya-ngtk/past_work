#include <stdio.h>
#include <stdlib.h>

extern void ps(const char *str, int fonttype);

extern unsigned int htab(unsigned int charpos);

extern void linefeed(unsigned int filenlineum);

extern void pagefeed(unsigned int filelinenum);

extern void filter(const char *str, int font);

void header(char *filename);

void stm(FILE *fp, int isWord);

enum FONT_TYPE {
    COURIER,
    COURIER_BOLD,
    MINCHO
};

enum FILE_TYPE {
    C_FILE,
    TEXT_FILE
};

