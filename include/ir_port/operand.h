#ifndef __IR_PORT_OPERAND__
#define __IR_PORT_OPERAND__
#include <ir.h>

ir_operand_kind ir_operand_get_kind(p_ir_operand p_operand);

// 函数、全局变量使用名字
char *ir_operand_get_sym_name(p_ir_operand p_operand);
// 局部、临时变量使用 id
size_t ir_operand_get_sym_id(p_ir_operand p_operand);

int ir_operand_get_int(p_ir_operand p_operand);
float ir_operand_get_float(p_ir_operand p_operand);

// 数组临时变量和局部、全局变量都使用 p_symbol_type
p_symbol_type ir_operand_get_sym_type(p_ir_operand p_operand);

#endif