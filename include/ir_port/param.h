#ifndef __IR_PORT_PARAM__
#define __IR_PORT_PARAM__
#include <ir.h>

// 获取参数的操作数
p_ir_operand ir_param_get_operand(p_ir_param p_param);
p_list_head ir_param_list_get_head(p_ir_param_list p_ir_param_list);

#endif