#include <ir_print.h>
#include <ir/instr.h>
#include <ir/basic_block.h>
#include <ir/func.h>
#include <stdio.h>

#include <symbol/sym.h>
void ir_instr_print(p_ir_instr p_instr)
{
    assert(p_instr);
    printf("    ");
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
            ir_binary_instr_print(p_instr->irkind, &p_instr->ir_binary);
            break;
        case ir_minus_op:
        case ir_not_op:
        case ir_int2float_op:
        case ir_float2int_op:
        case ir_val_assign:
            ir_unary_instr_print(p_instr->irkind, &p_instr->ir_unary);
            break;
        case ir_ret:
            ir_ret_instr_print(&p_instr->ir_ret);
            break;
        case ir_br:
            ir_br_instr_print(&p_instr->ir_br);
            break;
        case ir_condbr:
            ir_condbr_instr_print(&p_instr->ir_condbr);
            break;
        case ir_call:
            ir_call_instr_print(&p_instr->ir_call);
            break;
        case ir_array:
            ir_array_instr_print(&p_instr->ir_array);
            break;
        case ir_array_assign:
            ir_array_assign_instr_print(&p_instr->ir_array_assign);
    }
    printf("\n");
}

void ir_binary_instr_print(ir_instr_type instr_type, p_ir_binary_instr p_instr)
{
    ir_operand_print(p_instr->p_des);
    printf("= ");
    ir_operand_print(p_instr->p_src1);
    switch (instr_type) {
        case ir_add_op:
            printf("+ ");
            break;
        case ir_sub_op:
            printf("- ");
            break;
        case ir_mul_op:
            printf("* ");
            break;
        case ir_div_op:
            printf("/ ");
            break;
        case ir_mod_op:
            printf("%% ");
            break;
        case ir_and_op:
            printf("&& ");
            break;
        case ir_or_op:
            printf("|| ");
            break;
        case ir_eq_op:
            printf("== ");
            break;
        case ir_neq_op:
            printf("!= ");
            break;
        case ir_l_op:
            printf("< ");
            break;
        case ir_leq_op:
            printf("<= ");
            break;
        case ir_g_op:
            printf("> ");
            break;
        case ir_geq_op:
            printf(">= ");
            break;
        default:
            assert(0);
    }
    ir_operand_print(p_instr->p_src2);
}

void ir_unary_instr_print(ir_instr_type instr_type, p_ir_unary_instr p_instr)
{
    ir_operand_print(p_instr->p_des);
    printf("= ");
    switch (instr_type) {
        case ir_minus_op:
            printf("- ");
            break;
        case ir_not_op:
            printf("! ");
            break;
        case ir_int2float_op:
            printf("(float) ");
            break;
        case ir_float2int_op:
            printf("(int) ");
            break;
        case ir_val_assign:
            break;
        default:
            assert(0);
    }
    ir_operand_print(p_instr->p_src);
}

void ir_ret_instr_print(p_ir_ret_instr p_instr)
{
    printf("ret ");
    ir_operand_print(p_instr->p_ret);
}

void ir_br_instr_print(p_ir_br_instr p_instr)
{
    printf("br ");
    printf("b%ld", p_instr->p_target->block_id);
}

void ir_condbr_instr_print(p_ir_condbr_instr p_instr)
{
    printf("br ");
    ir_operand_print(p_instr->p_cond);
    printf(", ");
    printf("b%ld, ", p_instr->p_target_true->block_id);
    printf("b%ld", p_instr->p_target_false->block_id);
}

void ir_call_instr_print(p_ir_call_instr p_instr)
{
    ir_operand_print(p_instr->p_des);
    printf("= ");
    printf("@%s", p_instr->p_func->p_func_sym->name);
    ir_param_list_print(p_instr->p_param_list);
}

void ir_array_instr_print(p_ir_array_instr p_instr)
{
    ir_operand_print(p_instr->p_des);
    printf("= ");
    ir_operand_print(p_instr->p_array);
    printf("[");
    ir_operand_print(p_instr->p_offset);
    printf("]");
}

void ir_array_assign_instr_print(p_ir_array_assign_instr p_instr)
{
    ir_operand_print(p_instr->p_array);
    printf("[ ");
    ir_operand_print(p_instr->p_offset);
    printf("] ");
    printf("= ");
    ir_operand_print(p_instr->p_src);
}