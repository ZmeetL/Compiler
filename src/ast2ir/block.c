#include <ast/block.h>
#include <ast/stmt.h>
#include <ast2ir.h>
// 生成函数的函数体
p_ir_basic_block ast2ir_block_gen(p_ast2ir_info p_info, p_ast_block p_block) {
    assert(p_block);
    p_ir_basic_block p_entry = ir_basic_block_gen();
    ast2ir_info_add_basic_block(p_info, p_entry);
    p_list_head p_node;
    list_for_each(p_node, &p_block->stmt) {
        p_ast_stmt p_stmt = list_entry(p_node, ast_stmt, node);
        ast2ir_stmt_gen(p_info, NULL, NULL, p_stmt);
    }
    return p_entry;
}
