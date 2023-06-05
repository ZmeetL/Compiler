#include <ast_print.h>
#include <stdio.h>

#include <ast/func.h>
#include <symbol_print.h>

void ast_func_call_print(p_ast_func p_func, p_ast_param_list p_param_list) {
    assert(p_func);
    symbol_name_print(p_func->p_sym);
    printf("(");
    ast_param_list_print(p_param_list);
    printf(")");
}

void ast_func_decl_print(p_ast_func p_func) {
    assert(p_func);
    if (p_func->p_block) {
        symbol_init_print(p_func->p_sym);
        symbol_param_print(p_func->p_sym);
        ast_block_print(p_func->p_block);
    }
}
