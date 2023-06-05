#include <ast/func.h>
#include <ast2ir.h>

#include <symbol/sym.h>

// 生成函数 ir 将 p_info 传来的信息回馈给 ir_func
void ast2ir_func_gen(p_ast_func p_h_func, p_ir_func m_func_table) {
    p_ir_func p_m_func = m_func_table + p_h_func->p_sym->id;
    p_m_func->p_func_sym = p_h_func->p_sym;

    if (!p_h_func->p_block) return;

    p_ast2ir_info p_info = ast2ir_info_gen(p_m_func, m_func_table);
    p_ir_basic_block p_entry_block = ast2ir_block_gen(p_info, p_h_func->p_block);
    ir_func_add_basic_block(p_m_func, p_entry_block);

    ir_func_temp_sym_add(p_m_func, p_info->p_ret_operand->p_temp_sym);
    ast2ir_info_add_basic_block(p_info, p_info->p_ret_block);

    ir_func_set_block_id(p_m_func);
    ir_func_set_temp_id(p_m_func);
    ast2ir_info_drop(p_info);
}