#ifndef __IR_GEN_PROGRAM__
#define __IR_GEN_PROGRAM__
#include <ir/program.h>
p_ir_program ir_program_gen(size_t func_cnt);

p_ir_program ir_program_func_add(p_ir_program p_program, p_ir_func p_func);

void ir_program_drop(p_ir_program p_program);

#endif