#include "symbol.h"
#include <ast/exp.h>
#include <ast/func.h>
#include <ast2ir.h>

#include <symbol/sym.h>
#include <symbol/type.h>

// 根据 p_exp 生成指令并返回最后一条指令的左值
p_ir_operand ast2ir_exp_get_operand(p_ast2ir_info p_info, p_ast_exp p_exp) {
    p_ir_operand p_operand;
    switch (p_exp->kind) {
    case ast_exp_num: // 若是常量 直接返回该常量对应的操作数
        if (p_exp->basic == type_int) {
            return ir_operand_int_gen(p_exp->intconst);
        }
        if (p_exp->basic == type_float) {
            return ir_operand_float_gen(p_exp->floatconst);
        }
        assert(0);
    case ast_exp_val:
        // 若是变量 直接返回该变量对应的操作数
        p_operand = ir_operand_declared_sym_gen(p_exp->p_sym);
        if (p_exp->p_offset) // 若是数组元素赋值 需要新增一条语句将数组元素赋值给临时变量
        {
            p_ir_operand p_offset = ast2ir_exp_get_operand(p_info, p_exp->p_offset);
            p_ir_operand p_temp_des;
            p_ir_instr p_instr;
            if (p_exp->p_type->kind == type_var) {
                p_temp_des = ast2ir_operand_temp_sym_basic_gen(p_info, p_exp->p_type->basic);
                p_instr = ir_array_instr_gen(p_operand, p_offset, p_temp_des);
            }
            else {
                p_symbol_type p_type = p_exp->p_type;
                while (p_type->kind != type_var)
                    p_type = p_type->p_item;
                p_temp_des = ast2ir_operand_temp_sym_array_gen(p_info, p_type->basic);
                p_instr = ir_binary_instr_gen(ir_add_op, p_operand, p_offset, p_temp_des);
            }
            ast2ir_info_add_instr(p_info, p_instr);
            return ir_operand_copy(p_temp_des);
        }
        else
            return p_operand;
    default:
        p_operand = ir_instr_get_des(ast2ir_exp_gen(p_info, p_exp));
        return ir_operand_copy(p_operand);
    }
}

p_ir_instr ast2ir_exp_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    assert(p_exp);
    switch (p_exp->kind) {
    case ast_exp_exec:
        switch (p_exp->op) {
        case ast_exp_op_add:
        case ast_exp_op_sub:
        case ast_exp_op_mul:
        case ast_exp_op_div:
        case ast_exp_op_mod:

        case ast_exp_op_eq:
        case ast_exp_op_neq:
        case ast_exp_op_l:
        case ast_exp_op_leq:
        case ast_exp_op_g:
        case ast_exp_op_geq:
            return ast2ir_exp_exec_gen(p_info, p_exp);
        case ast_exp_op_assign:
            return ast2ir_exp_assign_gen(p_info, p_exp);
        case ast_exp_op_bool_not:
        case ast_exp_op_minus:
            return ast2ir_exp_uexec_gen(p_info, p_exp);
        default: // 逻辑运算先进行 condbr判断, 不会到达此
            assert(0);
        }
    case ast_exp_call:
        return ast2ir_exp_call_gen(p_info, p_exp);
    case ast_exp_num:
    case ast_exp_val:
    case ast_exp_str:
        return NULL;
    }
}

p_ir_instr ast2ir_exp_exec_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    assert(p_exp && p_exp->p_src_1 && p_exp->p_src_2);
    p_ir_operand p_operand1 = ast2ir_exp_get_operand(p_info, p_exp->p_src_1);
    p_ir_operand p_operand2 = ast2ir_exp_get_operand(p_info, p_exp->p_src_2);

    basic_type b_type;
    switch (p_exp->op) {
    case ast_exp_op_add:
    case ast_exp_op_sub:
    case ast_exp_op_mul:
    case ast_exp_op_div:
    case ast_exp_op_mod:
        b_type = p_exp->basic;
        break;
    case ast_exp_op_eq:
    case ast_exp_op_neq:
    case ast_exp_op_g:
    case ast_exp_op_geq:
    case ast_exp_op_l:
    case ast_exp_op_leq:
        b_type = type_int;
        break;
    default:
        assert(0);
    }
    p_ir_operand p_temp_des = ast2ir_operand_temp_sym_basic_gen(p_info, b_type);

    ir_instr_type ir_type;
    switch (p_exp->op) {
    case ast_exp_op_add:
        ir_type = ir_add_op;
        break;
    case ast_exp_op_sub:
        ir_type = ir_sub_op;
        break;
    case ast_exp_op_mul:
        ir_type = ir_mul_op;
        break;
    case ast_exp_op_div:
        ir_type = ir_div_op;
        break;
    case ast_exp_op_mod:
        ir_type = ir_mod_op;
        break;
    case ast_exp_op_eq:
        ir_type = ir_eq_op;
        break;
    case ast_exp_op_neq:
        ir_type = ir_neq_op;
        break;
    case ast_exp_op_g:
        ir_type = ir_g_op;
        break;
    case ast_exp_op_geq:
        ir_type = ir_geq_op;
        break;
    case ast_exp_op_l:
        ir_type = ir_l_op;
        break;
    case ast_exp_op_leq:
        ir_type = ir_leq_op;
        break;
    default:
        assert(0);
    }
    p_ir_instr p_new_instr = ir_binary_instr_gen(ir_type, p_operand1, p_operand2, p_temp_des);
    ast2ir_info_add_instr(p_info, p_new_instr);
    return p_new_instr;
}

p_ir_instr ast2ir_exp_uexec_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    assert(p_exp && p_exp->p_src_1);
    p_ir_operand p_operand = ast2ir_exp_get_operand(p_info, p_exp->p_src_1);
    p_ir_operand p_temp_des = NULL;
    p_ir_instr p_new_instr = NULL;
    switch (p_exp->op) {
    case ast_exp_op_bool_not:
        // 需要转换为 int 型
        p_temp_des = ast2ir_operand_temp_sym_basic_gen(p_info, type_int);
        p_new_instr = ir_unary_instr_gen(ir_not_op, p_operand, p_temp_des);
        break;
    case ast_exp_op_minus:
        p_temp_des = ast2ir_operand_temp_sym_basic_gen(p_info, ir_operand_get_basic_type(p_operand));
        p_new_instr = ir_unary_instr_gen(ir_minus_op, p_operand, p_temp_des);
        break;
    default:
        assert(0);
    }
    ast2ir_info_add_instr(p_info, p_new_instr);
    return p_new_instr;
}
// exp 正确则跳向 true, 错误跳向 false
p_ir_instr ast2ir_exp_cond_gen(p_ast2ir_info p_info, p_ir_basic_block p_true_block, p_ir_basic_block p_false_block, p_ast_exp p_exp) {
    assert(p_exp);
    p_ir_instr p_new_instr = NULL;
    if (p_exp->op == ast_exp_op_bool_or) {
        p_ir_basic_block p_new_false_block = ir_basic_block_gen();
        // 在当前 block 生成 左边代码
        ast2ir_exp_cond_gen(p_info, p_true_block, p_new_false_block, p_exp->p_src_1);

        // 在新block 生成右边代码， 该block 也是左边的 false block
        ast2ir_info_add_basic_block(p_info, p_new_false_block);
        p_new_instr = ast2ir_exp_cond_gen(p_info, p_true_block, p_false_block, p_exp->p_src_2);
    }
    else if (p_exp->op == ast_exp_op_bool_and) {
        p_ir_basic_block p_new_true_block = ir_basic_block_gen();
        // 在当前 block 生成 左边代码
        ast2ir_exp_cond_gen(p_info, p_new_true_block, p_false_block, p_exp->p_src_1);
        // 在新block 生成右边代码， 该block 也是左边的 true block
        ast2ir_info_add_basic_block(p_info, p_new_true_block);
        p_new_instr = ast2ir_exp_cond_gen(p_info, p_true_block, p_false_block, p_exp->p_src_2);
    }
    else {
        p_ir_operand p_cond = ast2ir_exp_get_operand(p_info, p_exp);
        p_new_instr = ir_condbr_instr_gen(p_info->p_current_basic_block, p_cond, p_true_block, p_false_block);
        ast2ir_info_add_instr(p_info, p_new_instr);
    }
    return p_new_instr;
}

p_ir_instr ast2ir_exp_assign_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    assert(p_exp);
    assert(p_exp->p_src_1 && p_exp->p_src_2);
    assert(p_exp->p_src_1->kind == ast_exp_val);

    p_ir_instr p_new_instr = NULL;
    p_ir_operand p_des = ir_operand_declared_sym_gen(p_exp->p_src_1->p_sym);
    if (p_exp->p_src_1->p_offset) { // 左值为数组对应指令为 数组赋值指令
        p_ir_operand p_offset = ast2ir_exp_get_operand(p_info, p_exp->p_src_1->p_offset);
        p_ir_operand p_src = ast2ir_exp_get_operand(p_info, p_exp->p_src_2);
        p_new_instr = ir_array_assign_instr_gen(p_des, p_offset, p_src);
    }
    else {
        p_ir_operand p_operand = ast2ir_exp_get_operand(p_info, p_exp->p_src_2);
        p_new_instr = ir_unary_instr_gen(ir_val_assign, p_operand, p_des);
    }
    ast2ir_info_add_instr(p_info, p_new_instr);
    return p_new_instr;
}

p_ir_instr ast2ir_exp_call_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    assert(p_exp && p_exp->kind == ast_exp_call);

    p_ir_func p_func = p_info->func_table + p_exp->p_func->p_sym->id;

    basic_type b_type = p_func->p_func_sym->p_type->basic;
    p_ir_operand p_des = ast2ir_operand_temp_sym_basic_gen(p_info, b_type);

    p_ir_param_list p_m_param_list = ast2ir_param_list_gen(p_info, p_exp->p_param_list);

    p_ir_instr p_new_instr = ir_call_instr_gen(p_func, p_m_param_list, p_des);
    ast2ir_info_add_instr(p_info, p_new_instr);

    return p_new_instr;
}