#include <ast_gen/func.h>

#include <ast_gen.h>

#include <symbol/sym.h>

p_ast_func ast_func_gen(p_symbol_item p_item, p_ast_block p_block) {
    p_ast_func p_func = malloc(sizeof(*p_func));
    *p_func = (ast_func) {
        .p_block = p_block,
        .p_sym = p_item->p_info,
        .node = list_init_head(&p_func->node),
    };
    p_item->p_func = p_func;
    return p_func;
}

void ast_func_drop(p_ast_func p_func) {
    assert(p_func);
    list_del(&p_func->node);

    if (p_func->p_block)
        ast_block_drop(p_func->p_block);
    free(p_func);
}
