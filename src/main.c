#include <ast2ir.h>
#include <frontend.h>

#include <ast_print.h>
#include <ir_print.h>

#include <ir_test.h>

int main(int argc, char *argv[]) {
    if (argc == 1)
        argv[argc++] = NULL;
    for (int i = 1; i < argc; ++i) {
        p_ast_program p_ast = frontend_trans(argv[i]);
        ast_program_print(p_ast);
        p_ir_program p_ir = ast2ir_program_gen(p_ast);
        ir_program_print(p_ir);
        ir_program_test(p_ir);
        ir_program_drop(p_ir);
    }
    return 0;
}