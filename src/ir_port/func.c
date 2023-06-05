#include <ir_port/func.h>
#include <ir/func.h>
p_list_head ir_func_get_basic_block_entry(p_ir_func p_func)
{
    return &p_func->entry_block;
}

p_symbol_sym ir_func_get_sym(p_ir_func p_func)
{
    return p_func->p_func_sym;
}