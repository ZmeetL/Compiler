#include <ast_print.h>
#include <stdio.h>

#include <ast/func.h>
#include <ast/program.h>

#include <symbol_print.h>

int deep = 0;

void ast_program_print(p_ast_program p_program) {
    p_list_head p_node;
    list_for_each(p_node, &p_program->func) {
        p_ast_func p_func = list_entry(p_node, ast_func, node);
        ast_func_decl_print(p_func);
    }

    symbol_store_print(p_program->p_store);
}
