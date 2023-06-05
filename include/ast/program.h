#ifndef __AST_PROGRAM__
#define __AST_PROGRAM__

#include <ast.h>
#include <ast/symbol_table.h>

struct ast_program {
    // list_head init;
    p_symbol_table p_table;

    list_head func;

    p_symbol_store p_store;
};

#endif