#include <ast_print.h>
#include <stdio.h>

#include <ast/stmt.h>

#include <symbol_print.h>

void ast_stmt_print(p_ast_stmt p_stmt) {
    assert(p_stmt);
    switch (p_stmt->type) {
    case ast_stmt_block:
        ast_block_print(p_stmt->p_block);
        break;
    case ast_stmt_exp:
        printf("%*s", deep, "");
        if (p_stmt->p_exp) ast_exp_print(p_stmt->p_exp);
        printf(";\n");
        break;
    case ast_stmt_return:
        printf("%*sreturn ", deep, "");
        if (p_stmt->p_exp) ast_exp_print(p_stmt->p_exp);
        printf(";\n");
        break;
    case ast_stmt_if_else:
        printf("%*sif(", deep, "");
        ast_exp_print(p_stmt->p_exp);
        printf(")\n");
        deep += 4;
        ast_stmt_print(p_stmt->p_stmt_1);
        deep -= 4;
        printf("%*selse\n", deep, "");
        deep += 4;
        ast_stmt_print(p_stmt->p_stmt_2);
        deep -= 4;
        break;
    case ast_stmt_while:
        printf("%*swhile(", deep, "");
        ast_exp_print(p_stmt->p_exp);
        printf(")\n");
        deep += 4;
        ast_stmt_print(p_stmt->p_stmt_1);
        deep -= 4;
        break;
    case ast_stmt_if:
        printf("%*sif(", deep, "");
        ast_exp_print(p_stmt->p_exp);
        printf(")\n");
        deep += 4;
        ast_stmt_print(p_stmt->p_stmt_1);
        deep -= 4;
        break;
    case ast_stmt_break:
        printf("%*sbreak;\n", deep, "");
        break;
    case ast_stmt_continue:
        printf("%*scontinue;\n", deep, "");
        break;
    }
}
