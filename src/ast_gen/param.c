#include <ast_gen/param.h>

#include <ast_gen.h>

p_ast_param_list ast_param_list_init(void) {
    p_ast_param_list p_param_list = malloc(sizeof(*p_param_list));
    *p_param_list = (ast_param_list) {
        .param = list_head_init(&p_param_list->param),
    };
    return p_param_list;
}
p_ast_param_list ast_param_list_add(p_ast_param_list p_param_list, p_ast_exp p_exp) {
    p_ast_param p_param = malloc(sizeof(*p_param));
    *p_param = (ast_param) {
        .p_exp = p_exp,
        .node = list_head_init(&p_param->node),
    };

    list_add_prev(&p_param->node, &p_param_list->param);
    return p_param_list;
}
void ast_param_drop(p_ast_param p_param) {
    assert(p_param);
    ast_exp_drop(p_param->p_exp);
    free(p_param);
}

void ast_param_list_drop(p_ast_param_list p_param_list) {
    assert(p_param_list);
    while (!list_head_alone(&p_param_list->param)) {
        p_ast_param p_param = list_entry(p_param_list->param.p_next, ast_param, node);
        list_del(&p_param->node);
        ast_param_drop(p_param);
    }
    free(p_param_list);
}