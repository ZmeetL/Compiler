#ifndef __AST2IR_OPERAND__
#define __AST2IR_OPERAND__

#include <ast2ir/info_gen.h>
p_ir_operand ast2ir_operand_temp_sym_array_gen(p_ast2ir_info p_info, basic_type b_type);
p_ir_operand ast2ir_operand_temp_sym_basic_gen(p_ast2ir_info p_info, basic_type b_type);

#endif