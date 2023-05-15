%{
#include <stdio.h>
extern int yylex();
void yyerror(const char* msg);
%}

%token INTEGER

%union {
    int integer; // 添加一个名为integer的成员
}

%type <integer> INTEGER
%type <integer> expression

%%
program : expression { printf("Result: %d\n", $1); }
        ;

expression : INTEGER '+' INTEGER { $$ = $1 + $3; }
           | INTEGER '-' INTEGER { $$ = $1 - $3; }
           ;

%%
int main() {
    yyparse();
    return 0;
}

void yyerror(const char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
}
