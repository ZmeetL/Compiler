
#include <ir_port/param.h>
#include <ir/param.h>


p_ir_operand ir_param_get_operand(p_ir_param p_param)
{
    return p_param->p_param;
}

p_list_head ir_param_list_get_head(p_ir_param_list p_ir_param_list)
{
    return &p_ir_param_list->param;
}