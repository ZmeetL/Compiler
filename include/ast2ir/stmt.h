#ifndef __AST2IR_STMT__
#define __AST2IR_STMT__

#include <ast2ir/info_gen.h>
p_ir_instr ast2ir_stmt_gen(p_ast2ir_info p_info, p_ir_basic_block while_start, p_ir_basic_block while_end_next, p_ast_stmt p_stmt);

p_ir_instr ast2ir_stmt_return_gen(p_ast2ir_info p_info, p_ast_exp p_exp);
p_ir_instr ast2ir_stmt_exp_gen(p_ast2ir_info p_info, p_ast_exp p_exp);
p_ir_instr ast2ir_stmt_break_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_end_next);
p_ir_instr ast2ir_stmt_continue_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start);
p_ir_instr ast2ir_stmt_if_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start, p_ir_basic_block p_while_end_next, p_ast_exp p_exp, p_ast_stmt p_stmt_1);
p_ir_instr ast2ir_stmt_if_else_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start, p_ir_basic_block p_while_end_next, p_ast_exp p_exp, p_ast_stmt p_stmt_1, p_ast_stmt p_stmt_2);
p_ir_instr ast2ir_stmt_while_gen(p_ast2ir_info p_info, p_ast_exp p_exp, p_ast_stmt p_stmt_1);
p_ir_instr ast2ir_stmt_block_gen(p_ast2ir_info p_info,
    p_ir_basic_block while_start, p_ir_basic_block while_end_next, p_ast_block p_block);
#endif