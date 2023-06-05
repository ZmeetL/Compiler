
#ifndef __IR_PROGRAM__
#define __IR_PROGRAM__
#include <ir.h>
struct ir_program {
    p_ir_func func_table;
    size_t func_cnt;

    p_symbol_store p_store;
};

#endif