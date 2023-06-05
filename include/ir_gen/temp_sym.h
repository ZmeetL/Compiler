#ifndef __IR_GEN_TEMP_SYM__
#define __IR_GEN_TEMP_SYM__

#include <ir/temp_sym.h>

p_ir_temp_sym ir_temp_sym_basic_gen(basic_type b_type, p_ir_func p_func);
p_ir_temp_sym ir_temp_sym_pointer_gen(basic_type b_type, p_ir_func p_func);

void ir_temp_sym_drop(p_ir_temp_sym p_temp_sym);
#endif