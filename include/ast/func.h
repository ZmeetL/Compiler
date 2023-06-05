#ifndef __AST_FUNC__
#define __AST_FUNC__

#include <ast.h>

struct ast_func {
    p_ast_block p_block;
    p_symbol_sym p_sym;

    list_head node;
};

#endif