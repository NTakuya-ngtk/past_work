#include "textformatter.h"

void linefeed(unsigned int filelinenum) {
    puts(" n ");
    if (filelinenum == 0) { //行番号は出力しない
        ps("     ", COURIER);
    } else {//行番号を出力
        char buffer[10];
        if (filelinenum >= 10000) //10000以上なら下4桁表示
            sprintf(buffer, "%04d ", filelinenum % 10000);
        else    //10000以下ならそのまま表示
            sprintf(buffer, "%4d ", filelinenum % 10000);
        ps(buffer, COURIER);
    }
}