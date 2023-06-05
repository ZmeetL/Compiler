#ifndef __IR_PORT_FUNC__
#define __IR_PORT_FUNC__
#include <ir.h>

p_list_head ir_func_get_basic_block_entry(p_ir_func p_func);

// 获取函数 symbol 信息
p_symbol_sym ir_func_get_sym(p_ir_func p_func);
#endif