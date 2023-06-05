
#include "ir_gen/basic_block.h" // 头文件包含还需考虑
#include <ir_print.h>
#include <ir/basic_block.h>
#include <ir/instr.h>

#include <stdio.h>
void ir_basic_block_print(p_ir_basic_block p_basic_block)
{
    assert(p_basic_block);

    printf("b%ld: ", p_basic_block->block_id);
    if (!list_head_alone(&p_basic_block->prev_basic_block_list)) {
        printf("                        ; preds = ");
        p_list_head p_node;
        list_for_each(p_node, &p_basic_block->prev_basic_block_list){
            size_t id = list_entry(p_node, ir_basic_block_list_node, node)->p_basic_block->block_id;
            printf("b%ld", id);
            if(p_node->p_next != &p_basic_block->prev_basic_block_list)
                printf(", ");
        }
    }
    printf("\n");

    p_list_head p_node;
    p_ir_instr p_instr = NULL;
    list_for_each(p_node, &p_basic_block->instr_list){
        p_instr = list_entry(p_node, ir_instr, node);
        ir_instr_print(p_instr);
    }
}
