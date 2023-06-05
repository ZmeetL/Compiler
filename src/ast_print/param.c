#include <ast_print.h>
#include <stdio.h>

#include <ast/param.h>

void ast_param_print(p_ast_param p_param) {
    assert(p_param);
    ast_exp_print(p_param->p_exp);
}

void ast_param_list_print(p_ast_param_list p_param_list) {
    assert(p_param_list);
    bool is_first = true;
    p_list_head p_node;
    list_for_each(p_node, &p_param_list->param) {
        if (!is_first) printf(", ");
        else
            is_first = false;

        p_ast_param p_param = list_entry(p_node, ast_param, node);
        ast_param_print(p_param);
    }
}