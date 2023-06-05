#ifndef __IR_GEN_BASIC_BLOCK__
#define __IR_GEN_BASIC_BLOCK__
#include <ir/basic_block.h>
p_ir_basic_block ir_basic_block_gen();
p_ir_basic_block ir_basic_block_add_prev(p_ir_basic_block p_prev, p_ir_basic_block p_next);

p_ir_basic_block ir_basic_block_addinstr(p_ir_basic_block p_basic_block, p_ir_instr p_instr);

void ir_basic_block_drop(p_ir_basic_block p_basic_block);

#endif