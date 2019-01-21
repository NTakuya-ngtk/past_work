#include "textformatter.h"

static int pagenum = 1;

void pagefeed(unsigned int filelinenum) {
    puts(" f ");
    header(NULL);
    linefeed(filelinenum);
}