#ifndef __IR_PORT_INSTR__
#define __IR_PORT_INSTR__
#include <ir.h>

p_ir_operand ir_instr_binary_get_src1(p_ir_instr p_instr);
p_ir_operand ir_instr_binary_get_src2(p_ir_instr p_instr);
p_ir_operand ir_instr_binary_get_des(p_ir_instr p_instr);

p_ir_operand ir_instr_unary_get_src(p_ir_instr p_instr);
p_ir_operand ir_instr_unary_get_des(p_ir_instr p_instr);

p_ir_operand ir_instr_ret_get_src(p_ir_instr p_instr);

p_ir_func ir_instr_call_get_func(p_ir_instr p_instr);
p_ir_operand ir_instr_call_get_des(p_ir_instr p_instr);
p_ir_param_list ir_instr_call_get_param(p_ir_instr p_instr);

p_ir_operand ir_instr_array_get_array(p_ir_instr p_instr);
p_ir_operand ir_instr_array_get_offset(p_ir_instr p_instr);
p_ir_operand ir_instr_array_get_des(p_ir_instr p_instr);

p_ir_operand ir_instr_array_assign_get_array(p_ir_instr p_instr);
p_ir_operand ir_instr_array_assign_get_offset(p_ir_instr p_instr);
p_ir_operand ir_instr_array_assign_get_src(p_ir_instr p_instr);

p_ir_basic_block ir_instr_br_get_target(p_ir_instr p_instr);

p_ir_operand ir_instr_condbr_get_cond(p_ir_instr p_instr);
p_ir_basic_block ir_instr_condbr_get_target_true(p_ir_instr p_instr);
p_ir_basic_block ir_instr_condbr_get_target_false(p_ir_instr p_instr);

ir_instr_type ir_instr_get_kind(p_ir_instr p_instr);
#endif