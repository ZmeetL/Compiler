#ifndef __IR_GEN_FUNC__
#define __IR_GEN_FUNC__
#include <ir/func.h>

p_ir_func ir_func_table_gen(size_t cnt);

void ir_func_add_basic_block(p_ir_func p_func, p_ir_basic_block p_basic_block);
void ir_func_temp_sym_add(p_ir_func p_func, p_ir_temp_sym p_temp_sym);

void ir_func_set_block_id(p_ir_func p_func);
void ir_func_set_temp_id(p_ir_func p_func);

void ir_func_table_drop(p_ir_func p_func, size_t cnt);
#endif