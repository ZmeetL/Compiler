%{
#include "parser.tab.h"
%}

%%
[0-9]+       { yylval.integer = atoi(yytext); return INTEGER; }
[ \t\n]      ; /* 忽略空格和换行符 */
.            { return yytext[0]; }
%%

int yywrap() {
    return 1;
}
