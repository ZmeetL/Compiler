#ifndef __IR_PORT_BASIC_BLOCK__
#define __IR_PORT_BASIC_BLOCK__

#include <ir.h>
p_ir_instr ir_basic_block_get_last_instr(p_ir_basic_block p_basic_block);
p_list_head ir_basic_block_get_instr_list_head(p_ir_basic_block p_basic_block);

bool ir_basic_block_get_if_visited(p_ir_basic_block p_basic_block);
size_t ir_basic_block_get_id(p_ir_basic_block p_basic_block);
// 返回该 基本块最后一条指令的正确跳转目标块， 没有返回 NULL
p_ir_basic_block ir_basic_block_get_true(p_ir_basic_block p_basic_block);
p_ir_basic_block ir_basic_block_get_false(p_ir_basic_block p_basic_block);

#endif