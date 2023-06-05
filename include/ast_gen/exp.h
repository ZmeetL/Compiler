#ifndef __AST_GEN_EXP__
#define __AST_GEN_EXP__

#include <ast/exp.h>
#include <ast/symbol_table.h>

basic_type ast_exp_get_basic(p_ast_exp p_exp);

p_ast_exp ast_exp_assign_gen(p_ast_exp lval, p_ast_exp rval);
p_ast_exp ast_exp_exec_gen(ast_exp_op op, p_ast_exp p_src_1, p_ast_exp p_src_2);
p_ast_exp ast_exp_lexec_gen(ast_exp_op op, p_ast_exp p_src_1, p_ast_exp p_src_2);
p_ast_exp ast_exp_uexec_gen(ast_exp_op op, p_ast_exp p_src_1);
p_ast_exp ast_exp_call_gen(p_symbol_item p_item, p_ast_param_list p_param_list);
p_ast_exp ast_exp_val_gen(p_symbol_sym p_sym);
p_ast_exp ast_exp_val_offset(p_ast_exp p_val, p_ast_exp p_offset);
p_ast_exp ast_exp_int_gen(INTCONST_t num);
p_ast_exp ast_exp_float_gen(FLOATCONST_t num);
p_ast_exp ast_exp_str_gen(p_symbol_str p_str);
void ast_exp_drop(p_ast_exp p_exp);

#endif