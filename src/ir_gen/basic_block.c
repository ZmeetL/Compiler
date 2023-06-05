
#include <ir_gen.h>
#include <ir_gen/basic_block.h>


p_ir_basic_block ir_basic_block_gen()
{
    p_ir_basic_block p_ir_block = malloc(sizeof(*p_ir_block));
    *p_ir_block = (ir_basic_block){
        .instr_list = list_head_init(&p_ir_block->instr_list),
        .prev_basic_block_list = list_head_init(&p_ir_block->prev_basic_block_list),
        .block_id = 0,
        .node = list_head_init(&p_ir_block->node),
    };
    return p_ir_block;
}
// 插入前驱节点列表
p_ir_basic_block ir_basic_block_add_prev(p_ir_basic_block p_prev, p_ir_basic_block p_next)
{
    p_ir_basic_block_list_node node = malloc(sizeof(*node));
    *node = (ir_basic_block_list_node){
        .p_basic_block = p_prev,
        .node = list_head_init(&node->node),
    };
    list_add_prev(&node->node, &p_next->prev_basic_block_list);
    return p_next;
}


p_ir_basic_block ir_basic_block_addinstr(p_ir_basic_block p_basic_block, p_ir_instr p_instr)
{
    list_add_prev(&p_instr->node, &p_basic_block->instr_list);
    return p_basic_block;
}



void ir_basic_block_drop(p_ir_basic_block p_basic_block)
{
    assert(p_basic_block);
    while (!list_head_alone(&p_basic_block->instr_list)) {
        p_ir_instr p_instr = list_entry(p_basic_block->instr_list.p_next, ir_instr, node);
        list_del(&p_instr->node);
        ir_instr_drop(p_instr);
    }
    while (!list_head_alone(&p_basic_block->prev_basic_block_list)) {
        p_ir_basic_block_list_node p_basic_block_list_node = list_entry(p_basic_block->prev_basic_block_list.p_next, ir_basic_block_list_node, node);
        list_del(&p_basic_block_list_node->node);
        free(p_basic_block_list_node);
    }
    free(p_basic_block);
}
