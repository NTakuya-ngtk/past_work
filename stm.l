%{
  /*
   * STM: State Transition Machine Module
   *         written by Yuki Furitsu
   */

#include <stdio.h>
#include <stdlib.h>
#include "textformatter.h"

%}

C_RESERVED ({NOT_ALPHANUM}*{C_WORDS}{NOT_ALPHANUM}*)
NOT_ALPHANUM (^[0-9A-Za-z_])
C_WORDS (auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while)
ASCII ({WORD}|{SPACE})
WORD ({IDENTIFIER}|{NUMBER}|{OPERATOR}) 
IDENTIFIER ([a-zA-Z_][0-9a-zA-Z_]*) 
NUMBER ({INTEGER}(\.{INTEGER})?([Ee][\+\-]?{INTEGER})?) 
INTEGER ([0-9]+) 
OPERATOR ({COMPOUNDOP}|{SINGLEOP}) 
COMPOUNDOP ("<>"|[<>:=]=|"..") 
SINGLEOP [\+\-\*/\.,:;=<>^\(\)\[\]\{\}#~\\!\?\"'\$%@&\|]
EUC [\200-\377]+
SPACE [ ]+
HORIZONTAL_TAB ("\t")
PAGEFEED ("\f")
LINEFEED ("\n")
COMMENT_LINE ("//")
COMMENT_START ("/*")
COMMENT_END ("*/")
DOUBLE_QUOTE ("\"")
BACKSLASH_DOUBLE_QUOTE ("\\\"")
SINGLE_QUOTE ("'")
BACKSLASH_SINGLE_QUOTE ("\\'")


%Start TEXT C_TEXT C_COMMENT_LINE C_COMMENT_START C_DOUBLE_QUOTE C_SINGLE_QUOTE

%%

<TEXT>{EUC} {
	filter(yytext, MINCHO);		/* Sends token and font to filter module (similar actions' comments abbrieviated below)*/
}

<TEXT>{HORIZONTAL_TAB} {
	filter(yytext, COURIER);
}

<TEXT>{LINEFEED} {
	filter(yytext, COURIER);
}

<TEXT>{PAGEFEED} {
	filter(yytext, COURIER);
}

<TEXT>{ASCII} {
	filter(yytext, COURIER);
}

<TEXT>. ;

<C_TEXT>{C_RESERVED} {
	filter(yytext, COURIER_BOLD);
}

<C_TEXT>{EUC} {
	filter(yytext, MINCHO);
}

<C_TEXT>{COMMENT_LINE} {
	filter(yytext, COURIER);
	BEGIN(C_COMMENT_LINE);	/* Enter to C_COMMENT_LINE mode */
}

<C_TEXT>{COMMENT_START} {
	filter(yytext, COURIER);
	BEGIN(C_COMMENT_START);	/* Enter to C_COMMENT_START mode */
}

<C_TEXT>{COMMENT_END} {
	filter(yytext, COURIER);	
}

<C_TEXT>{DOUBLE_QUOTE} {
	filter(yytext, COURIER);
	BEGIN(C_DOUBLE_QUOTE);	/* Enter to C_DOUBLE_QUOTE mode */
}

<C_TEXT>{BACKSLASH_DOUBLE_QUOTE} {
	filter(yytext, COURIER);		
}

<C_TEXT>{BACKSLASH_SINGLE_QUOTE} {
	filter(yytext, COURIER);		
}

<C_TEXT>{SINGLE_QUOTE} {
	filter(yytext, COURIER);
	BEGIN(C_SINGLE_QUOTE);	/* Enter to C_SINGLE_QUOTE mode */	
}

<C_TEXT>{HORIZONTAL_TAB} {
	filter(yytext, COURIER);
}

<C_TEXT>{LINEFEED} {
	filter(yytext, COURIER);
}

<C_TEXT>{PAGEFEED} {
	filter(yytext, COURIER);
}

<C_TEXT>{ASCII} {
	filter(yytext, COURIER);
}

<C_TEXT>. ;

<C_COMMENT_LINE>{EUC} {
  	filter(yytext, MINCHO);
}

<C_COMMENT_LINE>{HORIZONTAL_TAB} {
	filter(yytext, COURIER);
}


<C_COMMENT_LINE>{LINEFEED} {
	filter(yytext, COURIER);
	BEGIN(C_TEXT);	/* Enter to C_TEXT mode */
}

<C_COMMENT_LINE>{PAGEFEED} {
	filter(yytext, COURIER);
	BEGIN(C_TEXT);	/* Enter to C_TEXT mode */
}

<C_COMMENT_LINE>{COMMENT_END} {
	filter(yytext, COURIER);
	BEGIN(C_TEXT);	/* Enter to C_TEXT mode */
}

<C_COMMENT_LINE>{ASCII} {
	filter(yytext, COURIER);
}

<C_COMMENT_LINE>. ;

<C_COMMENT_START>{EUC} {
  	filter(yytext, MINCHO);;
}

<C_COMMENT_START>{HORIZONTAL_TAB} {
	filter(yytext, COURIER);
}

<C_COMMENT_START>{LINEFEED} {
	filter(yytext, COURIER);
}

<C_COMMENT_START>{PAGEFEED} {
	filter(yytext, COURIER);
}

<C_COMMENT_START>{COMMENT_END} {
	filter(yytext, COURIER);
	BEGIN(C_TEXT);	/* Enter to C_TEXT mode */
}

<C_COMMENT_START>{ASCII} {
	filter(yytext, COURIER);
}

<C_COMMENT_START>. ;

<C_DOUBLE_QUOTE>{EUC} {
  	filter(yytext, MINCHO);
}

<C_DOUBLE_QUOTE>{BACKSLASH_DOUBLE_QUOTE} {
	filter(yytext, COURIER);		
}

<C_DOUBLE_QUOTE>{DOUBLE_QUOTE} {
	filter(yytext, COURIER);
	BEGIN(C_TEXT);	/* Enter to C_TEXT mode */
}

<C_DOUBLE_QUOTE>{HORIZONTAL_TAB} {
	filter(yytext, COURIER);
}

<C_DOUBLE_QUOTE>{LINEFEED} {
	filter(yytext, COURIER);
}

<C_DOUBLE_QUOTE>{PAGEFEED} {

	filter(yytext, COURIER);
}

<C_DOUBLE_QUOTE>{ASCII} {
	filter(yytext, COURIER);
}

<C_DOUBLE_QUOTE>. ;

<C_SINGLE_QUOTE>{EUC} {
  	filter(yytext, MINCHO);
}

<C_SINGLE_QUOTE>{BACKSLASH_SINGLE_QUOTE} {
	filter(yytext, COURIER);		
}

<C_SINGLE_QUOTE>{SINGLE_QUOTE} {
	filter(yytext, COURIER);
	BEGIN(C_TEXT);	/* Enter to C_TEXT mode */
}

<C_SINGLE_QUOTE>{HORIZONTAL_TAB} {
	filter(yytext, COURIER);
}

<C_SINGLE_QUOTE>{LINEFEED} {
	filter(yytext, COURIER);
}

<C_SINGLE_QUOTE>{PAGEFEED} {
	filter(yytext, COURIER);
}

<C_SINGLE_QUOTE>{ASCII} {
	filter(yytext, COURIER);
}

<C_SINGLE_QUOTE>. ;

%%

void stm(FILE *fp, int isWord)
{
  yyin = fp;     /* Set input file */
  if(isWord==1){
    BEGIN(TEXT);     /* Initial mode for text file */
  }
  else if(isWord==0){
    BEGIN(C_TEXT);    /* Initial mode for C file */
  }
  yylex();       /* Call lexical analyzer */

}

