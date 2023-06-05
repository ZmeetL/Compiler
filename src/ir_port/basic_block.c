#include <ir_port/basic_block.h>
#include <ir/basic_block.h>
#include <ir/instr.h>

p_list_head ir_basic_block_get_instr_list_head(p_ir_basic_block p_basic_block)
{
    return &p_basic_block->instr_list;
}
p_ir_instr ir_basic_block_get_last_instr(p_ir_basic_block p_basic_block)
{
    return list_entry(p_basic_block->instr_list.p_prev, ir_instr, node);
}

size_t ir_basic_block_get_id(p_ir_basic_block p_basic_block)
{
    return p_basic_block->block_id;
}
// 返回该 基本块最后一条指令的正确跳转目标块， 没有返回 NULL
p_ir_basic_block ir_basic_block_get_true(p_ir_basic_block p_basic_block)
{
    p_ir_instr p_last_instr = ir_basic_block_get_last_instr(p_basic_block);
    if (p_last_instr->irkind == ir_br) {
        return p_last_instr->ir_br.p_target;
    }
    else if (p_last_instr->irkind ==  ir_condbr) {
        return p_last_instr->ir_condbr.p_target_true;
    }
    return NULL;
}

p_ir_basic_block ir_basic_block_get_false(p_ir_basic_block p_basic_block)
{
    p_ir_instr p_last_instr = ir_basic_block_get_last_instr(p_basic_block);
    if (p_last_instr->irkind ==  ir_condbr) {
        return p_last_instr->ir_condbr.p_target_false;
    }
    return NULL;
}