#ifndef __IRFUNC__
#define __IRFUNC__
#include <ir.h>

struct ir_func {
    p_symbol_sym p_func_sym;

    list_head entry_block;
    list_head temp_sym_head;
};

#endif