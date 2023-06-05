#include <ast/block.h>
#include <ast/stmt.h>
#include <ast2ir.h>

#include <symbol/sym.h>
#include <symbol/type.h>

p_ir_instr ast2ir_stmt_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start, p_ir_basic_block p_while_end_next, p_ast_stmt p_stmt) {
    switch (p_stmt->type) {
    case ast_stmt_return:
        return ast2ir_stmt_return_gen(p_info, p_stmt->p_exp);
    case ast_stmt_exp:
        return ast2ir_stmt_exp_gen(p_info, p_stmt->p_exp);
    case ast_stmt_block:
        return ast2ir_stmt_block_gen(p_info, p_while_start, p_while_end_next, p_stmt->p_block);
    case ast_stmt_if:
        return ast2ir_stmt_if_gen(p_info, p_while_start, p_while_end_next, p_stmt->p_exp, p_stmt->p_stmt_1);
    case ast_stmt_if_else:
        return ast2ir_stmt_if_else_gen(p_info, p_while_start, p_while_end_next, p_stmt->p_exp, p_stmt->p_stmt_1, p_stmt->p_stmt_2);
    case ast_stmt_while:
        return ast2ir_stmt_while_gen(p_info, p_stmt->p_exp, p_stmt->p_stmt_1);
    case ast_stmt_break:
        return ast2ir_stmt_break_gen(p_info, p_while_end_next);
    case ast_stmt_continue:
        return ast2ir_stmt_break_gen(p_info, p_while_start);
    }
}

// 将返回值全部放到 一个变量, 并跳转到 ret 块
p_ir_instr ast2ir_stmt_return_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    p_ir_operand p_ret = NULL;
    if (p_exp)
        p_ret = ast2ir_exp_get_operand(p_info, p_exp);
    else
        p_ret = ir_operand_void_gen();
    p_ir_operand p_ret_des = ir_operand_copy(p_info->p_ret_operand);
    p_ir_instr p_ret_assign_instr = ir_unary_instr_gen(ir_val_assign, p_ret, p_ret_des);
    ast2ir_info_add_instr(p_info, p_ret_assign_instr);
    p_ir_instr p_br_ret_instr = ir_br_instr_gen(p_info->p_current_basic_block, p_info->p_ret_block);
    ast2ir_info_add_instr(p_info, p_br_ret_instr);
    p_ir_basic_block p_next = ir_basic_block_gen();
    ast2ir_info_add_basic_block(p_info, p_next);
    return p_br_ret_instr;
}
p_ir_instr ast2ir_stmt_exp_gen(p_ast2ir_info p_info, p_ast_exp p_exp) {
    return ast2ir_exp_gen(p_info, p_exp);
}
// 跳转到循环体外并新建一个基本块作为之后指令写入的基本块
p_ir_instr ast2ir_stmt_break_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_end_next) {
    p_ir_instr p_br = ir_br_instr_gen(p_info->p_current_basic_block, p_while_end_next);
    ast2ir_info_add_instr(p_info, p_br);
    p_ir_basic_block p_next = ir_basic_block_gen();
    ast2ir_info_add_basic_block(p_info, p_next);
    return p_br;
}

p_ir_instr ast2ir_stmt_continue_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start) {
    p_ir_instr p_br = ir_br_instr_gen(p_info->p_current_basic_block, p_while_start);
    ast2ir_info_add_instr(p_info, p_br);
    p_ir_basic_block p_next = ir_basic_block_gen();
    ast2ir_info_add_basic_block(p_info, p_next);
    return p_br;
}

p_ir_instr ast2ir_stmt_if_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start, p_ir_basic_block p_while_end_next, p_ast_exp p_exp, p_ast_stmt p_stmt_1) {

    p_ir_basic_block p_true_block = ir_basic_block_gen();
    p_ir_basic_block p_next_block = ir_basic_block_gen();

    // 解析条件表达式
    p_ir_instr p_new_instr = ast2ir_exp_cond_gen(p_info, p_true_block, p_next_block, p_exp);

    // 解析 true 的 block
    ast2ir_info_add_basic_block(p_info, p_true_block);
    ast2ir_stmt_gen(p_info, p_while_start, p_while_end_next, p_stmt_1);

    // true block 的末尾添加跳转
    p_ir_instr p_true_block_br = ir_br_instr_gen(p_info->p_current_basic_block, p_next_block);
    ast2ir_info_add_instr(p_info, p_true_block_br);

    // 重新置当前写 block 为 p_next_block
    ast2ir_info_add_basic_block(p_info, p_next_block);
    return p_new_instr;
}

p_ir_instr ast2ir_stmt_if_else_gen(p_ast2ir_info p_info, p_ir_basic_block p_while_start, p_ir_basic_block p_while_end_next, p_ast_exp p_exp, p_ast_stmt p_stmt_1, p_ast_stmt p_stmt_2) {

    p_ir_basic_block p_true_block = ir_basic_block_gen();
    p_ir_basic_block p_false_block = ir_basic_block_gen();
    p_ir_basic_block p_next_block = ir_basic_block_gen();

    // 生成条件表达式
    p_ir_instr p_new_instr = ast2ir_exp_cond_gen(p_info, p_true_block, p_false_block, p_exp);

    // 生成 true 情况下的语句
    ast2ir_info_add_basic_block(p_info, p_true_block);
    ast2ir_stmt_gen(p_info, p_while_start, p_while_end_next, p_stmt_1);

    // 在 true_block 末尾添加跳转
    p_ir_instr p_true_block_br = ir_br_instr_gen(p_info->p_current_basic_block, p_next_block);
    ast2ir_info_add_instr(p_info, p_true_block_br);

    // 生成 false 情况下的语句
    ast2ir_info_add_basic_block(p_info, p_false_block);
    ast2ir_stmt_gen(p_info, p_while_start, p_while_end_next, p_stmt_2);

    // false 的末尾block 添加跳转
    p_ir_instr p_false_block_br = ir_br_instr_gen(p_info->p_current_basic_block, p_next_block);
    ast2ir_info_add_instr(p_info, p_false_block_br);

    // 重新置当前写 block 为 p_next_block
    ast2ir_info_add_basic_block(p_info, p_next_block);
    return p_new_instr;
}

p_ir_instr ast2ir_stmt_while_gen(p_ast2ir_info p_info, p_ast_exp p_exp, p_ast_stmt p_stmt_1) {
    // 转换成  do while

    p_ir_basic_block p_true_block = ir_basic_block_gen();
    p_ir_basic_block p_next_block = ir_basic_block_gen();

    // 解析条件表达式， 在当前块已经生成 条件跳转
    p_ir_instr p_condbr_outwhile = ast2ir_exp_cond_gen(p_info, p_true_block, p_next_block, p_exp);

    // 解析 while 循环体
    ast2ir_info_add_basic_block(p_info, p_true_block);
    ast2ir_stmt_gen(p_info, p_true_block, p_next_block, p_stmt_1);
    ast2ir_exp_cond_gen(p_info, p_true_block, p_next_block, p_exp);
    // 条件语句跳转已经生成完成，不用添加

    // 置当前写的块为下一块
    ast2ir_info_add_basic_block(p_info, p_next_block);

    return p_condbr_outwhile;
}
p_ir_instr ast2ir_stmt_block_gen(p_ast2ir_info p_info, p_ir_basic_block while_start, p_ir_basic_block while_end_next, p_ast_block p_block) {
    p_list_head p_node;
    p_ir_instr p_last_instr = NULL;
    list_for_each(p_node, &p_block->stmt) {
        p_ast_stmt p_stmt = list_entry(p_node, ast_stmt, node);
        p_last_instr = ast2ir_stmt_gen(p_info, while_start, while_end_next, p_stmt);
    }
    return p_last_instr;
}