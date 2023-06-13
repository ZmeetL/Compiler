/*
 * SysY.y : Parser for SysY language
 */

%define parse.error verbose
%param { yyscan_t yyscanner }

%{
#include <frontend/lexer.h>
#include <frontend/log.h>
#include <frontend/syntax_gen.h>

#define extra yyget_extra(yyscanner)
#define p_ast (extra->p_ast)

#define new_sym(name) ast_symbol_item_add(p_ast, name)
#define find_sym(name) ast_symbol_item_find(p_ast, name)
#define find_str(str) ast_symbol_str_get(p_ast, str)
%}

%initial-action
{
       p_ast = ast_program_gen();
}

%code requires{
#include <frontend/syntax.h>
}

%define api.pure full

%union {
       p_ast_block p_block;
       p_ast_stmt p_stmt;
       p_ast_exp p_exp;

       p_ast_program p_program;
       p_ast_func p_func;

       p_ast_param_list p_param_list;

       p_syntax_decl p_decl;
       p_syntax_decl_list p_decl_list;

       p_syntax_param_decl p_param_decl;
       p_syntax_param_list p_parameter_list;

       p_syntax_init p_init;

       basic_type type;

       ID_t ID;
       INTCONST_t INTCONST;
       FLOATCONST_t FLOATCONST;
       STRING_t STRING;
}
%type <p_exp> Cond
%type <p_exp> LOrExp
%type <p_exp> LAndExp
%type <p_exp> EqExp
%type <p_exp> RelExp

%type <p_exp> Exp
%type <p_exp> ConstExp
%type <p_exp> AddExp
%type <p_exp> MulExp
%type <p_exp> UnaryExp
%type <p_exp> PrimaryExp

%type <p_exp> Call
%type <p_exp> Val
%type <p_exp> Str

%type <p_exp> StmtExp
%type <p_stmt> Stmt

%type <p_block> BlockItems
%type <p_block> Block

%type <p_param_list> FuncRParamList
%type <p_param_list> FuncRParams

%type <p_func> FuncHead
%type <p_func> FuncDeclaration
%type <p_program> CompUnit
%type <p_program> CompUnitInit

%type <p_param_decl> ParameterDeclaration
%type <p_parameter_list> ParameterList
%type <p_parameter_list> Parameters

%type <p_decl> ArraryParameter
%type <p_decl> Declarator
%type <p_decl> VarInitDeclarator
%type <p_decl_list> VarInitDeclaratorList
%type <p_decl_list> VarDeclaration
%type <p_decl> ConstInitDeclarator
%type <p_decl_list> ConstInitDeclaratorList
%type <p_decl_list> ConstDeclaration
%type <p_decl_list> Declaration

%type <p_init> VarInitializer
%type <p_init> VarInitializerList
%type <p_init> ConstInitializer
%type <p_init> ConstInitializerList

%type <type> Type

%locations

%token UNSIGNED SIGNED
%token LONG SHORT
%token INT FLOAT DOUBLE CHAR
%token VOID
%token CONST VOLATILE
%token DO WHILE FOR BREAK CONTINUE
%token IF ELSE
%token RETURN

%token AND OR LE GE EQ NEQ
%token SELFADD SELFSUB

%token <INTCONST> INTCONST
%token <FLOATCONST> FLOATCONST
%token <ID> ID
%destructor { free($$); } ID
%token <STRING> STRING
%destructor { free($$); } STRING

%nonassoc NO_ELSE
%nonassoc ELSE

%%
begin : PUSHZONE CompUnit POPZONE
      ;

CompUnit : CompUnit Declaration     { syntax_global_vardecl(p_ast, $2); }
         | CompUnit FuncDeclaration { $$ = ast_program_func_add(p_ast, $2); }
         | CompUnitInit
         | CompUnit error
         ;

Type : INT   { $$ = type_int; }
     | FLOAT { $$ = type_float; }
     ;

Declaration : ConstDeclaration
            | VarDeclaration
            ;

ConstDeclaration : CONST Type ConstInitDeclaratorList ';' { $$ = syntax_decl_list_set($3, true, $2); }
                 ;

VarDeclaration : Type VarInitDeclaratorList ';' { $$ = syntax_decl_list_set($2, false, $1); }
               ;

ConstInitDeclaratorList : ConstInitDeclaratorList ',' ConstInitDeclarator { $$ = syntax_decl_list_add($1, $3); }
                        | ConstInitDeclarator                             { $$ = syntax_decl_list_add(syntax_decl_list_gen(), $1); }
                        ;

VarInitDeclaratorList : VarInitDeclaratorList ',' VarInitDeclarator { $$ = syntax_decl_list_add($1, $3); }
                      | VarInitDeclarator                           { $$ = syntax_decl_list_add(syntax_decl_list_gen(), $1); }
                      ;

ConstInitDeclarator : Declarator '=' ConstInitializer { $$ = syntax_decl_init($1, $3); }
                    ;

VarInitDeclarator : Declarator '=' VarInitializer { $$ = syntax_decl_init($1, $3); }
                  | Declarator                    { $$ = syntax_decl_init($1, NULL); }
                  ;

Declarator : Declarator '[' ConstExp ']' { $$ = syntax_decl_arr($1, $3); }
           | ID                          { $$ = syntax_decl_gen($1); }
           | Declarator error
           ;

ConstInitializer : '{' ConstInitializerList '}'     { $$ = $2; }
                 | '{' '}'                          { $$ = syntax_init_list_gen(); }
                 | ConstExp                         { $$ = syntax_init_exp_gen($1); }
                 ;

ConstInitializerList : ConstInitializerList ',' ConstInitializer { $$ = syntax_init_list_add($1, $3); }
                     | ConstInitializer                          { $$ = syntax_init_list_add(syntax_init_list_gen(), $1); }
                     ;

VarInitializer : '{' VarInitializerList '}'     { $$ = $2; }
               | '{' '}'                        { $$ = syntax_init_list_gen(); }
               | Exp                      { $$ = syntax_init_exp_gen($1); }
               ;

VarInitializerList : VarInitializerList ',' VarInitializer { $$ = syntax_init_list_add($1, $3); }
                   | VarInitializer                        { $$ = syntax_init_list_add(syntax_init_list_gen(), $1); }
                   ;

FuncHead : Type ID '(' Parameters ')' { $$ = syntax_func_head(p_ast, $1, $2, $4); }
         | VOID ID '(' Parameters ')' { $$ = syntax_func_head(p_ast, type_void, $2, $4); }
         ;

FuncDeclaration : FuncHead Block { $$ = syntax_func_end(p_ast, $1, $2); }
                ;

Parameters : ParameterList
           | /* *empty */  { $$ = syntax_param_list_gen(); }
           ;

ParameterList : ParameterList ',' ParameterDeclaration { $$ = syntax_param_list_add($1, $3); }
              | ParameterDeclaration                   { $$ = syntax_param_list_add(NULL, $1); }
              ;

ParameterDeclaration : Type ArraryParameter { $$ = syntax_param_decl_gen($1, $2); }
                     | Type ID              { $$ = syntax_param_decl_gen($1, syntax_decl_gen($2)); }
                     ;

ArraryParameter : ID '[' ']'                  { $$ = syntax_decl_arr(syntax_decl_gen($1), NULL); }
                | ArraryParameter '[' Exp ']' { $$ = syntax_decl_arr($1, $3); }
                ;

Cond : LOrExp
     ;

LOrExp : LOrExp OR LAndExp { $$ = ast_exp_lexec_gen(ast_exp_op_bool_or, $1, $3); }
       | LAndExp
       ;

LAndExp : LAndExp AND EqExp { $$ = ast_exp_lexec_gen(ast_exp_op_bool_and, $1, $3); }
        | EqExp
        ;

EqExp : EqExp EQ RelExp  { $$ = ast_exp_lexec_gen(ast_exp_op_eq, $1, $3); }
      | EqExp NEQ RelExp { $$ = ast_exp_lexec_gen(ast_exp_op_neq, $1, $3); }
      | RelExp
      ;

RelExp : RelExp '<' AddExp { $$ = ast_exp_lexec_gen(ast_exp_op_l, $1, $3); }
       | RelExp '>' AddExp { $$ = ast_exp_lexec_gen(ast_exp_op_g, $1, $3); }
       | RelExp LE AddExp  { $$ = ast_exp_lexec_gen(ast_exp_op_leq, $1, $3); }
       | RelExp GE AddExp  { $$ = ast_exp_lexec_gen(ast_exp_op_geq, $1, $3); }
       | AddExp
       ;

ConstExp : Exp { $$ = syntax_const_check($1); }
         ;

Exp : AddExp
    ;

AddExp : AddExp '+' MulExp { $$ = ast_exp_exec_gen(ast_exp_op_add, $1, $3); }
       | AddExp '-' MulExp { $$ = ast_exp_exec_gen(ast_exp_op_sub, $1, $3); }
       | MulExp
       ;

MulExp : MulExp '*' UnaryExp { $$ = ast_exp_exec_gen(ast_exp_op_mul, $1, $3); }
       | MulExp '/' UnaryExp { $$ = ast_exp_exec_gen(ast_exp_op_div, $1, $3); }
       | MulExp '%' UnaryExp { $$ = ast_exp_exec_gen(ast_exp_op_mod, $1, $3); }
       | UnaryExp
       ;

UnaryExp : '-' UnaryExp     { $$ = ast_exp_uexec_gen(ast_exp_op_minus, $2); }
         | '+' UnaryExp     { $$ = $2; }
         | '!' UnaryExp     { $$ = ast_exp_uexec_gen(ast_exp_op_bool_not, $2); }
         | PrimaryExp
         ;

PrimaryExp : '(' Exp ')' { $$ = $2; }
           | INTCONST    { $$ = ast_exp_int_gen($1); }
           | FLOATCONST  { $$ = ast_exp_float_gen($1); }
           | Val         { $$ = $1; }
           | Call        { $$ = $1; }
           | Str         { $$ = $1; }
           ;

Call : ID '(' FuncRParams ')' { $$ = ast_exp_call_gen(find_sym($1), $3); free($1); }
     ;

Val : ID                 { $$ = ast_exp_val_gen(find_sym($1)->p_info); free($1); }
    | Val '[' Exp ']'    { $$ = ast_exp_val_offset($1, $3); }
    ;

Str : STRING { $$ = ast_exp_str_gen(find_str($1)); free($1); }
    ;

FuncRParams : FuncRParamList { $$ = $1; }
            | /* *empty */   { $$ = ast_param_list_init(); }
            ;

FuncRParamList : FuncRParamList ',' Exp { $$ = ast_param_list_add($1, $3); }
               | Exp                    { $$ = ast_param_list_add(ast_param_list_init(), $1); }
               ;

Block : '{' BlockItems '}' { $$ = $2; }
      ;

BlockItems : BlockItems Declaration { $$ = syntax_local_vardecl(p_ast, $1, $2); }
           | BlockItems Stmt           { $$ = ast_block_add($1, $2); }
           | /* *empty */              { $$ = ast_block_gen(); }
           ;

StmtExp : /* *empty */ { $$ = NULL; }
        | Exp
        ;

Stmt : PUSHZONE Block POPZONE             { $$ = ast_stmt_block_gen($2); }
     | Val '=' Exp ';'                    { $$ = ast_stmt_exp_gen(ast_exp_assign_gen($1, $3)); }
     | StmtExp ';'                        { $$ = ast_stmt_exp_gen($1); }
     | RETURN StmtExp ';'                 { $$ = ast_stmt_return_gen($2); }
     | BREAK ';'                          { $$ = ast_stmt_break_gen(); }
     | CONTINUE ';'                       { $$ = ast_stmt_continue_gen(); }
     | IF '(' Cond ')' Stmt ELSE Stmt     { $$ = ast_stmt_if_else_gen($3, $5, $7); }
     | IF '(' Cond ')' Stmt %prec NO_ELSE { $$ = ast_stmt_if_gen($3, $5); }
     | WHILE '(' Cond ')' Stmt            { $$ = ast_stmt_while_gen($3, $5); }
     | error                              { $$ = ast_stmt_exp_gen(NULL); }
     ;

PUSHZONE : /* *empty */ { ast_symbol_zone_push(p_ast); }
         ;

POPZONE : /* *empty */ { ast_symbol_zone_pop(p_ast); }
        ;

CompUnitInit : /* *empty */ {
                     $$ = p_ast;
                     

                     p_symbol_type p_type = symbol_type_arrary_gen(0);
                     p_type->p_item = symbol_type_var_gen(type_int);
                     syntax_rtlib_decl(p_ast, type_int, "getarray", p_type, NULL, false);
                     p_type = symbol_type_arrary_gen(0);
                     p_type->p_item = symbol_type_var_gen(type_float);
                     syntax_rtlib_decl(p_ast, type_int, "getfarray", p_type, NULL, false);

                     syntax_rtlib_decl(p_ast, type_void, "putint", symbol_type_var_gen(type_int), NULL, false);
                     syntax_rtlib_decl(p_ast, type_void, "putch", symbol_type_var_gen(type_int), NULL, false);
                     syntax_rtlib_decl(p_ast, type_void, "putfloat", symbol_type_var_gen(type_float), NULL, false);

                     p_type = symbol_type_arrary_gen(0);
                     p_type->p_item = symbol_type_var_gen(type_int);
                     syntax_rtlib_decl(p_ast, type_void, "putarray", symbol_type_var_gen(type_int), p_type, false);
                     p_type = symbol_type_arrary_gen(0);
                     p_type->p_item = symbol_type_var_gen(type_float);
                     syntax_rtlib_decl(p_ast, type_void, "putfarray", symbol_type_var_gen(type_int), p_type, false);

                     syntax_rtlib_decl(p_ast, type_void, "putf", symbol_type_var_gen(type_str), NULL, true);

                     syntax_rtlib_decl(p_ast, type_void, "starttime", NULL, NULL, false);
                
              }
             ;
%%
