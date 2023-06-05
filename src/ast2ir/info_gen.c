#include <ast2ir/info_gen.h>
#include <symbol/sym.h>
#include <symbol/type.h>

// 根据函数信息 生成接下来需要收集的信息的返回值类型
p_ast2ir_info ast2ir_info_gen(p_ir_func p_m_func, p_ir_func m_func_table) {
    p_ast2ir_info p_info = malloc(sizeof(*p_info));
    *p_info = (ast2ir_info) {
        .p_current_basic_block = NULL,
        .p_func = p_m_func,
        .func_table = m_func_table,
        .p_ret_block = ir_basic_block_gen(),
    };
    p_ir_temp_sym p_temp_sym = ir_temp_sym_basic_gen(p_m_func->p_func_sym->p_type->basic, p_m_func);
    p_info->p_ret_operand = ir_operand_temp_sym_gen(p_temp_sym);

    p_ir_instr p_ret = ir_ret_instr_gen(p_info->p_ret_operand);
    ir_basic_block_addinstr(p_info->p_ret_block, p_ret);
    return p_info;
}

void ast2ir_info_drop(p_ast2ir_info p_info) {
    free(p_info);
}

void ast2ir_info_add_basic_block(p_ast2ir_info p_info, p_ir_basic_block p_new) {
    ir_func_add_basic_block(p_info->p_func, p_new);
    p_info->p_current_basic_block = p_new;
}
void ast2ir_info_add_instr(p_ast2ir_info p_info, p_ir_instr p_instr) {
    ir_basic_block_addinstr(p_info->p_current_basic_block, p_instr);
}