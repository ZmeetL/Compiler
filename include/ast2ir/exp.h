#ifndef __AST2IR_INSTR__
#define __AST2IR_INSTR__

#include <ast2ir/info_gen.h>

p_ir_instr ast2ir_exp_gen(p_ast2ir_info p_info, p_ast_exp p_exp);
p_ir_operand ast2ir_exp_get_operand(p_ast2ir_info p_info, p_ast_exp p_exp);

p_ir_instr ast2ir_exp_assign_gen(p_ast2ir_info p_info, p_ast_exp p_exp);

p_ir_instr ast2ir_exp_cond_gen(p_ast2ir_info p_info, p_ir_basic_block p_true_block, p_ir_basic_block p_false_block, p_ast_exp p_exp);

p_ir_instr ast2ir_exp_exec_gen(p_ast2ir_info p_info, p_ast_exp p_exp);
p_ir_instr ast2ir_exp_uexec_gen(p_ast2ir_info p_info, p_ast_exp p_exp);
p_ir_instr ast2ir_exp_call_gen(p_ast2ir_info p_info, p_ast_exp p_exp);
p_ir_instr ast2ir_exp_array_gen(p_ast2ir_info p_info, p_ast_exp p_exp);

#endif