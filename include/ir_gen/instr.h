#ifndef __IR_GEN_INSTR__
#define __IR_GEN_INSTR__
#include <ir/instr.h>

p_ir_instr ir_binary_instr_gen(ir_instr_type ir_type, p_ir_operand p_src1, p_ir_operand p_src2, p_ir_operand des);
p_ir_instr ir_unary_instr_gen(ir_instr_type ir_type, p_ir_operand p_src, p_ir_operand p_des);

p_ir_instr ir_call_instr_gen(p_ir_func p_func, p_ir_param_list p_param_list, p_ir_operand p_des);
p_ir_instr ir_array_instr_gen(p_ir_operand p_array, p_ir_operand p_offset, p_ir_operand p_des);
p_ir_instr ir_array_assign_instr_gen(p_ir_operand p_sym, p_ir_operand p_offset, p_ir_operand p_src);
p_ir_instr ir_ret_instr_gen(p_ir_operand p_src);
p_ir_instr ir_br_instr_gen(p_ir_basic_block p_current_basic_block, p_ir_basic_block p_target);
p_ir_instr ir_condbr_instr_gen(p_ir_basic_block p_current_basic_block, p_ir_operand p_cond, p_ir_basic_block p_target_true, p_ir_basic_block p_target_false);

p_ir_operand ir_instr_get_src1(p_ir_instr p_instr);
p_ir_operand ir_instr_get_src2(p_ir_instr p_instr);
p_ir_operand ir_instr_get_des(p_ir_instr p_instr);

void ir_instr_drop(p_ir_instr p_instr);
#endif