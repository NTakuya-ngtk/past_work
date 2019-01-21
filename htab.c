#include "textformatter.h"

unsigned int htab(unsigned int charpos) {
    int i;
    char buff[9];
    //あと何文字スペースを出力するか
    unsigned int count = 8 - (charpos % 8);
    for (i = 0; i < count; i++) {
        buff[i] = ' ';
        buff[i + 1] = '\0';
    }

    //スペースを出力
    ps(buff, COURIER);
    return charpos + count;
}


