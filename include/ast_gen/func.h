#ifndef __AST_GEN_FUNC__
#define __AST_GEN_FUNC__

#include <ast/func.h>
#include <ast/symbol_table.h>

p_ast_func ast_func_gen(p_symbol_item p_item, p_ast_block p_block);
void ast_func_drop(p_ast_func p_func);

#endif