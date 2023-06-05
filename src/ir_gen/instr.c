#include <ir_gen/instr.h>
#include <ir_gen.h>

p_ir_instr ir_binary_instr_gen(ir_instr_type ir_type, p_ir_operand p_src1, p_ir_operand p_src2, p_ir_operand p_des)
{
    p_ir_instr p_instr = NULL;
    switch (ir_type) {
        case ir_add_op:
        case ir_sub_op:
        case ir_mul_op:
        case ir_div_op:
        case ir_mod_op:
        case ir_and_op:
        case ir_or_op:
        case ir_eq_op:
        case ir_neq_op:
        case ir_l_op:
        case ir_leq_op:
        case ir_g_op:
        case ir_geq_op:

        p_instr = malloc(sizeof(*p_instr));
        *p_instr = (ir_instr){
            .irkind = ir_type,
            .ir_binary = (ir_binary_instr){
                .p_src1 = p_src1,
                .p_src2 = p_src2,
                .p_des = p_des,
            },
            .node = list_head_init(&p_instr->node),
        };
        break;
        default:
            assert(0);
    }
    return p_instr;
}

p_ir_instr ir_unary_instr_gen(ir_instr_type ir_type, p_ir_operand p_src, p_ir_operand p_des)
{
    p_ir_instr p_instr = NULL;
    switch (ir_type) {
        case ir_minus_op:
        case ir_not_op:
        case ir_int2float_op:
        case ir_float2int_op:
        case ir_val_assign:

        p_instr = malloc(sizeof(*p_instr));
        *p_instr = (ir_instr){
            .irkind = ir_type,
            .ir_unary = (ir_unary_instr){
                .p_src = p_src,
                .p_des = p_des,
            },
            .node = list_head_init(&p_instr->node),
        };
        break;
        default:
            assert(0);
    }
    return p_instr;
}

p_ir_instr ir_ret_instr_gen(p_ir_operand p_src)
{
    p_ir_instr p_instr = malloc(sizeof(*p_instr));
    
    *p_instr = (ir_instr){
        .irkind = ir_ret,
        .ir_ret = (ir_ret_instr){
            .p_ret = p_src,
        },
        .node = list_head_init(&p_instr->node),
    };

    return p_instr;
}

p_ir_instr ir_br_instr_gen(p_ir_basic_block p_current_basic_block, p_ir_basic_block p_target)
{
    p_ir_instr p_instr = malloc(sizeof(*p_instr));

    *p_instr = (ir_instr){
        .irkind = ir_br,
        .ir_br = (ir_br_instr){
            .p_target = p_target,
        },
        .node = list_head_init(&p_instr->node),
    };
    ir_basic_block_add_prev(p_current_basic_block, p_target);
    return p_instr;
}

p_ir_instr ir_condbr_instr_gen(p_ir_basic_block p_current_basic_block, p_ir_operand p_cond, p_ir_basic_block p_target_true, p_ir_basic_block p_target_false)
{
    p_ir_instr p_instr = malloc(sizeof(*p_instr));

    *p_instr = (ir_instr){
        .irkind = ir_condbr,
        .ir_condbr = (ir_condbr_instr){
            .p_cond = p_cond,
            .p_target_true = p_target_true,
            .p_target_false = p_target_false,
        },
        .node = list_head_init(&p_instr->node),
    };
    ir_basic_block_add_prev(p_current_basic_block, p_target_true);
    ir_basic_block_add_prev(p_current_basic_block, p_target_false);
    return p_instr;
}

p_ir_instr ir_call_instr_gen(p_ir_func p_func, p_ir_param_list p_param_list, p_ir_operand p_des)
{
    p_ir_instr p_instr = malloc(sizeof(*p_instr));

    *p_instr = (ir_instr){
        .irkind = ir_call,
        .ir_call = (ir_call_instr){
            .p_func = p_func,
            .p_des = p_des,
            .p_param_list = p_param_list,
        },
        .node = list_head_init(&p_instr->node),
    };
    return p_instr;
}

p_ir_instr ir_array_instr_gen(p_ir_operand p_array, p_ir_operand p_offset, p_ir_operand p_des)
{
    p_ir_instr p_instr = malloc(sizeof(*p_instr));
    *p_instr = (ir_instr){
        .irkind = ir_array,
        .ir_array = (ir_array_instr){
            .p_array = p_array,
            .p_des = p_des,
            .p_offset = p_offset,
        },
        .node = list_head_init(&p_instr->node),
    };
    return p_instr;
}

p_ir_instr ir_array_assign_instr_gen(p_ir_operand p_array, p_ir_operand p_offset, p_ir_operand p_src)
{
    p_ir_instr p_instr = malloc(sizeof(*p_instr));
    *p_instr = (ir_instr){
        .irkind = ir_array_assign,
        .ir_array_assign = (ir_array_assign_instr){
            .p_array = p_array,
            .p_src = p_src,
            .p_offset = p_offset,
        },
        .node = list_head_init(&p_instr->node),
    };
    return p_instr;
}


p_ir_operand ir_instr_get_src1(p_ir_instr p_instr)
{
    switch (p_instr->irkind) {
        case ir_add_op:
        case ir_sub_op:
        case ir_mul_op:
        case ir_div_op:
        case ir_mod_op:
        case ir_and_op:
        case ir_or_op:
        case ir_eq_op:
        case ir_neq_op:
        case ir_l_op:
        case ir_leq_op:
        case ir_g_op:
        case ir_geq_op:
            return p_instr->ir_binary.p_src1;
        case ir_minus_op:
        case ir_not_op:
        case ir_int2float_op:
        case ir_float2int_op:
        case ir_val_assign:
            return p_instr->ir_unary.p_src;
        default:
            return NULL;
    }
}
p_ir_operand ir_instr_get_src2(p_ir_instr p_instr)
{
    switch (p_instr->irkind) {
        case ir_add_op:
        case ir_sub_op:
        case ir_mul_op:
        case ir_div_op:
        case ir_mod_op:
        case ir_and_op:
        case ir_or_op:
        case ir_eq_op:
        case ir_neq_op:
        case ir_l_op:
        case ir_leq_op:
        case ir_g_op:
        case ir_geq_op:
            return p_instr->ir_binary.p_src2;
        default:
            return NULL;
    }
}
p_ir_operand ir_instr_get_des(p_ir_instr p_instr)
{
    switch (p_instr->irkind) {
        case ir_add_op:
        case ir_sub_op:
        case ir_mul_op:
        case ir_div_op:
        case ir_mod_op:
        case ir_and_op:
        case ir_or_op:
        case ir_eq_op:
        case ir_neq_op:
        case ir_l_op:
        case ir_leq_op:
        case ir_g_op:
        case ir_geq_op:
            return p_instr->ir_binary.p_des;
        case ir_minus_op:
        case ir_not_op:
        case ir_int2float_op:
        case ir_float2int_op:
        case ir_val_assign:
            return p_instr->ir_unary.p_des;
        case ir_call:
            return p_instr->ir_call.p_des;
        case ir_array:
            return p_instr->ir_array.p_des;
        default:
            return NULL;
    }
}

// 操作数已经被存在单独的列表中
void ir_instr_drop(p_ir_instr p_instr)
{
    assert(p_instr);
    switch (p_instr->irkind) {
        case ir_add_op:
        case ir_sub_op:
        case ir_mul_op:
        case ir_div_op:
        case ir_mod_op:
        case ir_and_op:
        case ir_or_op:
        case ir_eq_op:
        case ir_neq_op:
        case ir_l_op:
        case ir_leq_op:
        case ir_g_op:
        case ir_geq_op:
            ir_operand_drop(p_instr->ir_binary.p_src1);
            ir_operand_drop(p_instr->ir_binary.p_src2);
            ir_operand_drop(p_instr->ir_binary.p_des);
            break;
        case ir_minus_op:
        case ir_not_op:
        case ir_int2float_op:
        case ir_float2int_op:
        case ir_val_assign:
            ir_operand_drop(p_instr->ir_unary.p_src);
            ir_operand_drop(p_instr->ir_unary.p_des);
            break;
        case ir_call:
            ir_operand_drop(p_instr->ir_call.p_des);
            ir_param_list_drop(p_instr->ir_call.p_param_list);
            break;
        case ir_array_assign:
            ir_operand_drop(p_instr->ir_array_assign.p_array);
            ir_operand_drop(p_instr->ir_array_assign.p_offset);
            ir_operand_drop(p_instr->ir_array_assign.p_src);
            break;
        case ir_array:
            ir_operand_drop(p_instr->ir_array.p_array);
            ir_operand_drop(p_instr->ir_array.p_offset);
            ir_operand_drop(p_instr->ir_array.p_des);
            break;
        case ir_ret:
            ir_operand_drop(p_instr->ir_ret.p_ret);
            break;
        case ir_br:
            break;
        case ir_condbr:
            ir_operand_drop(p_instr->ir_condbr.p_cond);
            break;
    }
    free(p_instr);
}
