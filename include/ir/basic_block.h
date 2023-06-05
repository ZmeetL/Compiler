#ifndef __IR_BASIC_BLOCK
#define __IR_BASIC_BLOCK

#include "ir.h"

struct ir_basic_block {
    size_t block_id;
    list_head instr_list;

    list_head prev_basic_block_list;
    list_head node;
};

struct ir_basic_block_list_node {
    p_ir_basic_block p_basic_block;
    list_head node;
};

#endif