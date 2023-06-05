#ifndef __AST_EXP__
#define __AST_EXP__

#include <ast.h>

enum ast_exp_op {
    ast_exp_op_assign,

    ast_exp_op_bool_or,
    ast_exp_op_bool_and,

    ast_exp_op_eq,
    ast_exp_op_neq,
    ast_exp_op_l,
    ast_exp_op_leq,
    ast_exp_op_g,
    ast_exp_op_geq,

    ast_exp_op_add,
    ast_exp_op_sub,
    ast_exp_op_mul,
    ast_exp_op_div,
    ast_exp_op_mod,

    ast_exp_op_bool_not,
    ast_exp_op_minus,
};
struct ast_exp {
    enum {
        ast_exp_exec,
        ast_exp_call,
        ast_exp_val,
        ast_exp_num,
        ast_exp_str,
    } kind;
    union {
        struct {
            p_ast_exp p_src_1, p_src_2;
            ast_exp_op op;
        }; // exec
        struct {
            p_symbol_sym p_sym;
            p_ast_exp p_offset;
            p_symbol_type p_type;
        }; // call val
        struct {
            p_ast_func p_func;
            p_ast_param_list p_param_list;
        };
        union {
            INTCONST_t intconst; // int
            FLOATCONST_t floatconst; // float
        };
        p_symbol_str p_str;
    };
    basic_type basic;
};

#endif