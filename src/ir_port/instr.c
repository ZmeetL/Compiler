#include <ir_port/instr.h>
#include <ir/instr.h>

p_ir_operand ir_instr_binary_get_src1(p_ir_instr p_instr)
{
    return p_instr->ir_binary.p_src1;
}
p_ir_operand ir_instr_binary_get_src2(p_ir_instr p_instr)
{
    return p_instr->ir_binary.p_src2;
}
p_ir_operand ir_instr_binary_get_des(p_ir_instr p_instr)
{
    return p_instr->ir_binary.p_des;
}
p_ir_operand ir_instr_unary_get_src(p_ir_instr p_instr)
{
    return p_instr->ir_unary.p_src;
}
p_ir_operand ir_instr_unary_get_des(p_ir_instr p_instr)
{
    return p_instr->ir_unary.p_des;
}
p_ir_operand ir_instr_ret_get_src(p_ir_instr p_instr)
{
    return p_instr->ir_ret.p_ret;
}
p_ir_func ir_instr_call_get_func(p_ir_instr p_instr)
{
    return p_instr->ir_call.p_func;
}
p_ir_operand ir_instr_call_get_des(p_ir_instr p_instr)
{
    return p_instr->ir_call.p_des;
}
p_ir_param_list ir_instr_call_get_param(p_ir_instr p_instr)
{
    return p_instr->ir_call.p_param_list;
}
p_ir_operand ir_instr_array_get_array(p_ir_instr p_instr)
{
    return p_instr->ir_array.p_array;
}
p_ir_operand ir_instr_array_get_offset(p_ir_instr p_instr)
{
    return p_instr->ir_array.p_offset;
}
p_ir_operand ir_instr_array_get_des(p_ir_instr p_instr)
{
    return p_instr->ir_array.p_des;
}

p_ir_operand ir_instr_array_assign_get_array(p_ir_instr p_instr)
{
    return p_instr->ir_array_assign.p_array;
}
p_ir_operand ir_instr_array_assign_get_offset(p_ir_instr p_instr)
{
    return p_instr->ir_array_assign.p_offset;
}
p_ir_operand ir_instr_array_assign_get_src(p_ir_instr p_instr)
{
    return p_instr->ir_array_assign.p_src;
}
p_ir_basic_block ir_instr_br_get_target(p_ir_instr p_instr)
{
    return p_instr->ir_br.p_target;
}
p_ir_operand ir_instr_condbr_get_cond(p_ir_instr p_instr)
{
    return p_instr->ir_condbr.p_cond;
}
p_ir_basic_block ir_instr_condbr_get_target_true(p_ir_instr p_instr)
{
    return p_instr->ir_condbr.p_target_true;
}
p_ir_basic_block ir_instr_condbr_get_target_false(p_ir_instr p_instr)
{
    return p_instr->ir_condbr.p_target_false;
}

ir_instr_type ir_instr_get_kind(p_ir_instr p_instr)
{
    return p_instr->irkind;
}