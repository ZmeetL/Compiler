#include <ast_print.h>
#include <stdio.h>

#include <ast/block.h>
#include <ast/stmt.h>

void ast_block_print(p_ast_block p_block) {
    assert(p_block);
    printf("%*s{\n", deep, "");
    deep += 4;
    p_list_head p_node;
    list_for_each(p_node, &p_block->stmt) {
        p_ast_stmt p_stmt = list_entry(p_node, ast_stmt, node);
        ast_stmt_print(p_stmt);
    }
    deep -= 4;
    printf("%*s}\n", deep, "");
}