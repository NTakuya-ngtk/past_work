#define LINELENGTH 80   //一行の文字数
#define PAGELINES 56    //1ページの行数
#define BUFFER (LINELENGTH*3 + 10)  //バッファサイズ


#include "textformatter.h"

static unsigned int filelinenum = 1;
static unsigned int outlinenum = 1;
static unsigned int charpos = 0;

/// 文字列を80文字以内に収まるようにbufferにコピーします。
/// \param src source of string
/// \param buffer buffer for splited string
/// \param charpos a current character position of line
/// \return length of buffer.( = strlen(buffer) )
int stringcopy(const char *src, char buffer[BUFFER], int charpos) {
    const char *start = src;
    int count = 0;
    for (; *src != '\0' && (charpos + count) < LINELENGTH;) {
        if (((*src) & 0x80) == 0) //英字
        {
            //escape
            if (*src == '\\' || *src == '(' || *src == ')')
            {
                *buffer++ = '\\';
            }
            *buffer++ = *src++;
            count++;
        } else {  //日本語2bytes
            *buffer++ = *src++;
            *buffer++ = *src++;
            count += 2;
        }
    }
    *buffer = '\0';
    return count;
}

/// 現在の文字位置を確認し、改ページや改行が必要なら行う
/// \param online 1行の文字数を越えた場合の改行なら1、\nや\fによる改行なら1
/// \return 改ページしたなら0、改ページしなかったら1
int poscheck(int online) {

    int linebroken = 0; //改行を行うかどうかのフラグ

    // 一行の行数が越えているかの判定
    if (charpos >= LINELENGTH) {
        outlinenum++;
        charpos = 0;
        linebroken = 1;
    }

    // 1ページの行数を越えているかどうか
    if (outlinenum > PAGELINES) {
        outlinenum = 1;
        charpos = 0;
        if(online)  //改ページ時に行番号を表示するかどうか
            pagefeed(0);
        else
            pagefeed(filelinenum);
        return 0;
    }

    //改行が必要なら、この地点で改行
    if (linebroken) {
        linefeed(0);
    }
    return 1;
}

void filter(const char *str, int font) {
    char buff[BUFFER];

    switch (str[0]) {
        case '\t':  //タブ
            poscheck(0);
            charpos = htab(charpos);
            return;
        case '\n': {    //改行
            filelinenum++;
            outlinenum++;
            charpos = 0;
            int res = poscheck(0);
            if (res)linefeed(filelinenum);  //行番号が出力済みでなければ行番号と改行文字を出力
            return;
        }
        case '\f':  //改ページ
            poscheck(0);
            filelinenum++;
            outlinenum = 1;
            charpos = 0;
            pagefeed(filelinenum);
            return;
        default:    //制御文字以外
            while (*str != '\0') {;
                poscheck(1);
                int length = stringcopy(str, buff, charpos);    //バッファにコピーする
                str += length;
                charpos += length;
                ps(buff, font);
            }
    }

}
