#ifndef __IR_INSTR__
#define __IR_INSTR__
#include <ir.h>
enum ir_instr_type {
    // binary instr
    ir_add_op,
    ir_sub_op,
    ir_mul_op,
    ir_div_op,
    ir_mod_op,
    ir_and_op,
    ir_or_op,
    ir_eq_op,
    ir_neq_op,
    ir_l_op,
    ir_leq_op,
    ir_g_op,
    ir_geq_op,

    // unary instr
    ir_minus_op,
    ir_not_op,
    ir_int2float_op,
    ir_float2int_op,
    ir_val_assign,
    // memory instr
    // ir_alloca,
    // ir_store,
    // ir_load,

    // other
    ir_array_assign,
    ir_call,
    ir_array,
    ir_ret,
    ir_br,
    ir_condbr,
};

struct ir_binary_instr {
    p_ir_operand p_src1, p_src2, p_des;
};

struct ir_unary_instr {
    p_ir_operand p_src, p_des;
};

struct ir_call_instr {
    p_ir_func p_func;
    p_ir_param_list p_param_list;
    p_ir_operand p_des;
};

struct ir_array_instr {
    p_ir_operand p_array;
    p_ir_operand p_offset;
    p_ir_operand p_des;
};

struct ir_array_assign_instr {
    p_ir_operand p_array;
    p_ir_operand p_offset;
    p_ir_operand p_src;
};
struct ir_ret_instr {
    p_ir_operand p_ret; //  NULL 时返回 void
};

struct ir_br_instr {
    p_ir_basic_block p_target;
};

struct ir_condbr_instr {
    p_ir_basic_block p_target_true, p_target_false;
    p_ir_operand p_cond;
};

struct ir_instr {
    ir_instr_type irkind;
    union {
        ir_binary_instr ir_binary;
        ir_unary_instr ir_unary;
        ir_call_instr ir_call;
        ir_array_instr ir_array;
        ir_array_assign_instr ir_array_assign;
        ir_ret_instr ir_ret;
        ir_br_instr ir_br;
        ir_condbr_instr ir_condbr;
    };

    list_head node; // 下一条指令
};

// 分配 des 的类型 变量给 des
// struct ir_alloca_instr{
//     p_ir_symbol des;
// };

// struct ir_load_instr{
//     p_ir_symbol src;
//     p_ir_symbol des;
// };

// struct ir_store_instr{
//     p_ir_symbol src;
//     p_ir_symbol des;
// };

#endif