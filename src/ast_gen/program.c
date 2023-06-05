#include <ast_gen/program.h>
#include <ast_gen/symbol_table.h>

#include <ast_gen.h>
#include <symbol_gen.h>

p_ast_program ast_program_gen(void) {
    p_ast_program p_program = malloc(sizeof(*p_program));
    *p_program = (ast_program) {
        .p_table = symbol_table_gen(),
        .p_store = symbol_store_gen(),
        .func = list_init_head(&p_program->func),
    };
    return p_program;
}
void ast_program_drop(p_ast_program p_program) {
    assert(p_program);
    symbol_table_drop(p_program->p_table);

    while (!list_head_alone(&p_program->func)) {
        p_ast_func p_del = list_entry(p_program->func.p_next, ast_func, node);
        ast_func_drop(p_del);
    }

    free(p_program);
}

p_ast_program ast_program_func_add(p_ast_program p_program, p_ast_func p_func) {
    list_add_prev(&p_func->node, &p_program->func);
    return p_program;
}

p_symbol_item ast_symbol_item_add(p_ast_program p_program, p_symbol_sym p_sym, bool is_global) {
    p_symbol_item p_item = symbol_table_item_add(p_program->p_table, p_sym);
    if (!p_item) return NULL;

    if (p_sym->p_type->kind >= type_func) {
        symbol_store_add_function(p_program->p_store, p_sym);
    }
    else {
        if (is_global) {
            symbol_store_add_global(p_program->p_store, p_sym);
        }
        else {
            symbol_store_add_local(p_program->p_store, p_sym);
        }
    }

    return p_item;
}
p_symbol_item ast_symbol_item_find(p_ast_program p_program, const char *name) {
    return symbol_table_item_find(p_program->p_table, name);
}

p_symbol_str ast_symbol_str_get(p_ast_program p_program, const char *string) {
    p_symbol_str p_str = symbol_table_str_get(p_program->p_table, string);
    symbol_store_add_str(p_program->p_store, p_str);
    return p_str;
}

void ast_symbol_zone_push(p_ast_program p_program) {
    symbol_table_zone_push(p_program->p_table);
}
void ast_symbol_zone_pop(p_ast_program p_program) {
    symbol_table_zone_pop(p_program->p_table);
}