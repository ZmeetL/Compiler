#ifndef __AST__
#define __AST__

#include <symbol.h>
#include <util.h>

typedef int64_t INTCONST_t;
typedef double FLOATCONST_t;
typedef char *STRING_t;
typedef char *ID_t;

typedef struct ast_program ast_program, *p_ast_program;
typedef struct ast_param ast_param, *p_ast_param;
typedef struct ast_param_list ast_param_list, *p_ast_param_list;
typedef struct ast_func ast_func, *p_ast_func;
typedef struct ast_block ast_block, *p_ast_block;
typedef struct ast_stmt ast_stmt, *p_ast_stmt;
typedef struct ast_exp ast_exp, *p_ast_exp;
typedef enum ast_exp_op ast_exp_op;

#endif