/*
モジュール名；ヘッダモジュール
作成者：永田拓也
作成開始日：2017年5月11日
最終更新日：2017年5月11日
概要：テキストフォーマッタで出来上がる書式にヘッダを付けるプログラム
 */

#include "textformatter.h"
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <string.h>

void header(char *filename) {


    /*各種変数宣言*/
    static int pagenum = 0; //出力するページ番号
    time_t atime, rtime; //タイム関数のポインタを格納する変数
    struct passwd *pwd; //ユーザ名を格納する変数
    struct tm *t; //構造体形式のローカルファイル保存
    char date[50]; //取得した日付を格納する型変数
    char page[20];  //ページ数を格納するchar型変数
    static char FILENAME[91]; //ファイル名を格納

    /*ファイル名を90字で打ち切り*/
    if (filename != NULL) {
        strncpy(FILENAME, filename, 90);
        FILENAME[90] = '\0';
    }


    /*page番号インクリメント*/
    pagenum = pagenum + 1;
    printf("%%%%Page: %d %d\n b\n", pagenum, pagenum);


    /*char型の変数へページ番号を格納*/
    sprintf(page, "page %d", pagenum);




    /*経過秒を取得*/
    atime = time(&rtime);

    /*構造体形式のローカル時間に変換*/
    t = localtime(&atime);

    /*char型の変数へ日付を格納*/
    sprintf(date, "%d/%d/%d", t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);

    /*ユーザIDをchar型変数へ格納する*/

    pwd = getpwuid(getuid());

    /*ポストスクリプトモジュールへの受け渡し部*/

    ps(FILENAME, COURIER);
    printf("n");
    ps(page, COURIER);
    printf("n");
    ps(date, COURIER);
    printf("n");
    ps(pwd->pw_name, COURIER);
    printf("n");
    printf("(----------) C s");
    if (filename)linefeed(1);



    /*モジュールテスト使用部*/
    //  printf("%s\n%s\n%s\n%s\n",filename,page,date,pwd->pw_name);



    return;

}

//モジュールテスト様のメイン関数
/*
int main()
{

  char *file = "file";

  header(file);

  return 0;
}
*/
