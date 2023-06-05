#ifndef __IR_PORT_PROGRAM__
#define __IR_PORT_PROGRAM__
#include <ir.h>
// 获取全局 变量 list
p_list_head ir_program_get_global_list(p_ir_program p_program);
p_ir_func ir_program_get_func_table(p_ir_program p_program);

#endif