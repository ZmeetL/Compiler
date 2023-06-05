#include <ir_test.h>

#include <ir/basic_block.h>

#include <util/list.h>

memory_type ir_basic_block_test(p_list_head p_list, memory_stack **global_stack, memory_stack **top_stack) {
    p_ir_basic_block p_basic_block = list_entry(p_list->p_next, ir_basic_block, node);
    assert(p_basic_block);
    p_list_head p_node = &p_basic_block->instr_list;
    return ir_instr_test(p_node, &(*global_stack), &(*top_stack));
}