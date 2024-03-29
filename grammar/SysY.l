/*
 * SysY.l : Scanner for SysY language
 */

%{
#include <frontend/yyextra.h>
#include <frontend/parser.h>
#include <frontend/log.h>

#include <util/log.h>

#include <limits.h>

INTCONST_t str2int(const char *text, int base, YYLTYPE *loc, yyscan_t scanner);
FLOATCONST_t str2float(const char *text, YYLTYPE *loc, yyscan_t scanner);
%}

%option reentrant bison-bridge bison-locations
%option yylineno batch noinput nounput noyywrap

%option extra-type="p_extra_info"

%x MULTICOMMENT
%x LINECOMMENT

%x header



LE   (<=)
GE   (>=)
EQ   (==)
NEQ  (!=)
AND  (&&)
OR   (\|\|)

INT       (int)
FLOAT     (float)
VOID      (void)
CONST     (const)
WHILE     (while)
BREAK     (break)
CONTINUE  (continue)
IF        (if)
ELSE      (else)
RETURN    (return)

BLANK     ([ \t\r\a])
NEWLINE   ([\n])

ID        ([_a-zA-Z][_a-zA-Z0-9]*)

HEXINTCONST  (0[xX][0-9a-fA-F]+)
OCTINTCONST  (0[0-7]*)
DECINTCONST  ([1-9][0-9]*)

HEXFLOATCONST  ((0[xX])(([0-9a-fA-F]*\.?[0-9a-fA-F]+)|([0-9a-fA-F]+\.))([pP][-+]?[0-9]+))
DECFLOATCONST  (([0-9]+[eE][-+]?[0-9]+)|((([0-9]+\.)|([0-9]*\.[0-9]+))([eE][-+]?[0-9]+)?))

STRING (["][^"\n]*["])


%%


[+] {printf("ADD +\n"); return yytext[0];}
[-] {printf("SUB -\n"); return yytext[0];}
[*] {printf("MUL *\n"); return yytext[0];}
[/] {printf("DIV /\n"); return yytext[0];}
[%] {printf("MOD %%\n"); return yytext[0];}
[(] {printf("LPARENT (\n"); return yytext[0];}
[)] {printf("RPARENT )\n"); return yytext[0];}
[{] {printf("LBRACE {\n"); return yytext[0];}
[}] {printf("RBRACE }\n"); return yytext[0];}
[\[] {printf("LK [\n"); return yytext[0];}
[\]] {printf("RK ]\n"); return yytext[0];}
[;] {printf("SEMICN ;\n"); return yytext[0];}
[<] {printf("LT <\n"); return yytext[0];}
[>] {printf("RT >\n"); return yytext[0];}
[=] {printf("ASSIGN =\n"); return yytext[0];}
[,] {printf("COMMA ,\n"); return yytext[0];}


{LE}  {printf("LE <=\n"); return LE;  }
{GE}  {printf("GE >=\n"); return GE;  }
{EQ}  {printf("EQ ==\n"); return EQ;  }
{NEQ} {printf("NEQ !=\n"); return NEQ; }
{AND} {printf("AND &&\n"); return AND; }
{OR}  {printf("OR ||\n"); return OR;  }

{BLANK}+   { /* empty space */ }
{NEWLINE}+ { /* empty lines */ Line = Line + 1;}

{INT}      {printf("INT int\n"); return INT;      }
{FLOAT}    {printf("FLOAT float\n"); return FLOAT;    }
{VOID}     {printf("VOID void\n"); return VOID;     }
{CONST}    {printf("CONST const\n"); return CONST;    }
{WHILE}    {printf("WHILE while\n"); return WHILE;    }
{BREAK}    {printf("BREAK break\n"); return BREAK;    }
{CONTINUE} {printf("CONTINUE continue\n"); return CONTINUE; }
{IF}       {printf("IF if\n"); return IF;       }
{ELSE}     {printf("ELSE else\n"); return ELSE;     }
{RETURN}   {printf("RETURN return\n"); return RETURN;   }

{ID} {
    char *node = malloc(sizeof(*node) * (strlen(yytext) + 1));
    strcpy(node, yytext);
    yylval->ID = node;
    printf("ID %s\n", node);
    return ID;
}

{DECINTCONST} {
    INTCONST_t val = str2int(yytext, 10, yylloc, yyscanner);
    yylval->INTCONST = val;
    printf("INTCONST %ld\n", val);
    return INTCONST;
}
{OCTINTCONST} {
    INTCONST_t val = str2int(yytext, 8, yylloc, yyscanner);
    yylval->INTCONST = val;
    printf("INTCONST %ld\n", val);
    return INTCONST;
}
{HEXINTCONST} {
    INTCONST_t val = str2int(yytext, 16, yylloc, yyscanner);
    yylval->INTCONST = val;
    printf("INTCONST %ld\n", val);
    return INTCONST;
}

{DECFLOATCONST} {
    FLOATCONST_t val = str2float(yytext, yylloc, yyscanner);
    yylval->FLOATCONST = val;
    printf("FLOATCONST %f\n", val);
    return FLOATCONST;
}
{HEXFLOATCONST} {
    FLOATCONST_t val = str2float(yytext, yylloc, yyscanner);
    yylval->FLOATCONST = val;
    printf("FLOATCONST %f\n", val);
    return FLOATCONST;
}

{STRING} {
    size_t length = strlen(yytext) - 2;
    char *str = malloc(sizeof(*str) * length + 1);
    strncpy(str, yytext + 1, length);
    str[length] = '\0';
    yylval->STRING = str;
    printf("STRING %s\n", str);
    return STRING;
}

[/][/] { BEGIN(LINECOMMENT); }
<LINECOMMENT>[^\\\n]+
<LINECOMMENT>[\\]+/[^\n]
<LINECOMMENT>([\\][\n])+
<LINECOMMENT>[\n] { BEGIN(INITIAL); }

[/][*] { BEGIN(MULTICOMMENT); }
<MULTICOMMENT>[^*]+
<MULTICOMMENT>[*]+/[^/]
<MULTICOMMENT>[*][/] { BEGIN(INITIAL); }

^[ \t]*#[ \t]*include[ \t]* { BEGIN(header); }
<header>[<][^\n>]+[>] { yytext[yyleng - 1] = '\0'; frontend_push_file(yytext + 1, yylloc, yyextra, yyscanner); BEGIN(INITIAL); }
<header>["][^\n"]+["] { yytext[yyleng - 1] = '\0'; frontend_push_file(yytext + 1, yylloc, yyextra, yyscanner); BEGIN(INITIAL); }

^[ \t]*#[ \t]*endfile { if (frontend_pop_file(yyextra, yyscanner)) yyterminate(); }
<<EOF>> { if (frontend_pop_file(yyextra, yyscanner)) yyterminate(); }

. { yyerror(yylloc, yyscanner, "lexical error, unexpected \"%s\"", yytext); };
%%
INTCONST_t str2int(const char *text, int base, YYLTYPE *loc, yyscan_t scanner) {
    char *endptr;
    errno = 0;
    INTCONST_t tmp = strtoll(text, &endptr, base);
    if(text[0] == '0')
    {   
        if(text[1] == 'x' || text[1] == 'X')
        {
            for(int i = 2; text[i] != '\0'; ++i)
            {
                if((text[i] > 'F' && text[i] <= 'Z')||(text[i] > 'f' && text[i] <= 'z'))
                {
                    yyerror(loc, scanner, "lexical error, HEXINTCONST ERROR\"%s\": %m", text);
                    printf("[Error] [frontend] Line  %d: syntax error, HEXINTCONST ERROR %s\n", Line, text);
                    tmp = 0;
                    errno = 0;
                    return tmp;
                }
            }
        }
        else 
        {
            for(int i = 1; text[i] != '\0'; ++i)
            if(text[i] > '7') 
            {
                yyerror(loc, scanner, "lexical error, OCTINTCONST ERROR\"%s\": %m", text);
                printf("[Error] [frontend] Line  %d: syntax error, HEXINTCONST ERROR %s\n", Line, text);
                tmp = 0;
                errno = 0;
                return tmp;
            }
        }
    }
    if ((errno == ERANGE && tmp == LLONG_MAX)) {
        yyerror(loc, scanner, "lexical error, integer constant too big\"%s\": %m", text);
        tmp = 0;
        errno = 0;
    }
    if (*endptr != '\0') {
        yyerror(loc, scanner, "integer constant suffix \"%s\"", endptr);
    }
    return tmp;
}
FLOATCONST_t str2float(const char *text, YYLTYPE *loc, yyscan_t scanner) {
    char *endptr;
    errno = 0;
    FLOATCONST_t tmp = strtod(text, &endptr);
    if (errno == ERANGE) {
        yyerror(loc, scanner, "lexical error, wrong float constant \"%s\": %m", text);
        tmp = 0;
        errno = 0;
    }
    if (*endptr != '\0') {
        yyerror(loc, scanner, "float constant suffix \"%s\"", endptr);
    }
    return tmp;
}

