#include <ast2ir.h>
#include <ast_gen.h>
#include <symbol/store.h>
#include <symbol/sym.h> // 这合适吗 ？

#include <ast/func.h>
p_ir_program ast2ir_program_gen(p_ast_program p_h_program) {
    p_ir_program p_m_program = ir_program_gen(list_entry(p_h_program->func.p_prev, ast_func, node)->p_sym->id + 1);
    p_m_program->p_store = p_h_program->p_store;
    p_list_head p_node;
    list_for_each(p_node, &p_h_program->func) {
        p_ast_func p_h_func = list_entry(p_node, ast_func, node);
        ast2ir_func_gen(p_h_func, p_m_program->func_table);
    }
    ast_program_drop(p_h_program);
    return p_m_program;
}