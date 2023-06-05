#include <ast/exp.h>
#include <ast2ir.h>

// 主要解决 int a[2][3]; t = a[2]; 存储 array 类型
p_ir_operand ast2ir_operand_temp_sym_array_gen(p_ast2ir_info p_info, basic_type b_type) {
    p_ir_operand p_new_op = ir_operand_temp_sym_gen(ir_temp_sym_pointer_gen(b_type, p_info->p_func));
    return p_new_op;
}

p_ir_operand ast2ir_operand_temp_sym_basic_gen(p_ast2ir_info p_info, basic_type b_type) {
    p_ir_operand p_new_op = ir_operand_temp_sym_gen(ir_temp_sym_basic_gen(b_type, p_info->p_func));
    return p_new_op;
}