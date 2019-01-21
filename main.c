/*
ファイル名:main.c
モジュール名:メインもジュール
作成者:山本遼人
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "textformatter.h"

void printMacro(void);

int main(int argc, char *argv[]) {
  FILE *fp;
  enum FILE_TYPE type;

  /*引数は3つ以下でなければならない*/
  if (argc > 3) {
    fprintf(stderr, "Usage:%s [-c] <filename>\n", argv[0]);
    exit(1);
  }


  /*引数の数によって場合分けをする*/
  switch (argc) {
  case 1:
    printMacro(); //マクロ定義を標準出力
    header("stdin");
    fp = stdin;
    type = TEXT_FILE;
    break;
  case 2:
    if (strcmp(argv[1], "-c") == 0) {
      printMacro(); //マクロ定義を標準出力
      header("stdin");
      fp = stdin;
      type = C_FILE;
    } else {
      if ((fp = fopen(argv[1], "r")) == NULL) {
	fprintf(stderr, "can't open %s\n", argv[1]);
	exit(1);
      }
      printMacro(); //マクロ定義を標準出力
      header(argv[1]);
      type = TEXT_FILE;
    }
    break;
  case 3:
    if (strcmp(argv[1], "-c") == 0) {
      if ((fp = fopen(argv[2], "r")) == NULL) {
	fprintf(stderr, "can't open %s\n", argv[2]);
	exit(1);
      }
      printMacro(); //マクロ定義を標準出力
      header(argv[2]);
      type = C_FILE;
    }
    break;
  default:
    break;
  }

  stm(fp, type);    //stmを呼び出す
  printf("f");

  fclose(fp);
  return 0;
}


void printMacro(void) {
    printf("%%!PS-Adobe-1.0\n");
    printf("%%%%Pages: (atend)\n");
    printf("%%%%BoundingBox: (atend)\n");
    printf("%%%%EndComments\n\n");
    printf("%%\n");
    printf("%% $Id: prologue.ps,v 1.7 1994/04/10 08:33:40 yamamoto Exp yamamoto $\n");
    printf("%%\n\n");
    printf("%% General macros.\n");
    printf("/curx {currentpoint pop} def\n");
    printf("/cury {currentpoint exch pop} def\n\n");
    printf("%% Constans.		% Japanese character scale factor.\n");
    printf("/jscale 0.94 def\n\n");
    printf("%% Commands.\n");
    printf("/n {			%% - n -\n");
    printf("	sx cury dy sub moveto\n");
    printf("} def\n\n");
    printf("/f {                  %% - f -\n");
    printf("      showpage\n");
    printf("} def\n\n");
    printf("/s {			%% string font s -\n");
    printf("	dup K eq\n");
    printf("	{js}\n");
    printf("	{setfont show}\n");
    printf("	ifelse\n");
    printf("} def\n\n");
    printf("/js {			%% string font js -\n");
    printf("	setfont\n");
    printf("	dw 0 rmoveto\n");
    printf("	dw 2 mul exch 0 exch ashow\n");
    printf("	dw neg 0 rmoveto\n");
    printf("} def\n\n");
    printf("%% Initialization.\n");
    printf("/init {			%% sx sy pt dy init -\n");
    printf("	gsave\n\n");
    printf("	/dy exch def\n");
    printf("	/pt exch def\n");
    printf("	/sy exch def\n");
    printf("	/sx exch def\n\n");
    printf("	fonts {\n");
    printf("		findfont pt scalefont def\n");
    printf("	} forall\n");
    printf("	jfonts {\n");
    printf("		findfont pt jscale mul scalefont def\n");
    printf("	} forall\n\n");
    printf("	%% Dummy.\n");
    printf("	0 0 moveto\n\n");
    printf("	%% Set character width.\n");
    printf("	C setfont\n");
    printf("	/asciiwidth (AA) stringwidth pop def\n");
    printf("	K setfont\n");
    printf("	/japanesewidth <2422> stringwidth pop def\n");
    printf("	/dw asciiwidth japanesewidth sub 2 div def\n\n");
    printf("	grestore\n");
    printf("} def\n\n");
    printf("%% Default fonts.\n");
    printf("/fonts 3 dict def\n");
    printf("fonts begin\n");
    printf("	/B /Courier-Bold def			%% Bold\n");
    printf("	/C /Courier def					%% Courier\n");
    printf("end\n");
    printf("/jfonts 3 dict def\n");
    printf("jfonts begin\n");
    printf("	/K /Ryumin-Light-EUC-H def		%% Kanji (Mincho-tai)\n");
    printf("end\n\n");
    printf("25 768 10 12 init\n");
    printf("/b {sx sy moveto} def\n");
    printf("%%%%EndProlog\n");
}
