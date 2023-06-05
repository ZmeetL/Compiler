#ifndef __IR_GEN_OPERAND__
#define __IR_GEN_OPERAND__

#include <ir/operand.h>
p_ir_operand ir_operand_int_gen(int intconst);
p_ir_operand ir_operand_float_gen(float floatconst);
p_ir_operand ir_operand_void_gen(void);

p_ir_operand ir_operand_declared_sym_gen(p_symbol_sym p_ir_sym);

p_ir_operand ir_operand_temp_sym_gen(p_ir_temp_sym p_temp_sym);

basic_type ir_operand_get_basic_type(p_ir_operand p_operand);

p_ir_operand ir_operand_copy(p_ir_operand p_operand);

// 设置 临时变量 id 返回下一个 id
size_t ir_operand_set_temp_var_id(size_t id, p_ir_operand p_operand);

void ir_operand_drop(p_ir_operand p_operand);
#endif