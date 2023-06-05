#include <ir/program.h>
#include <ir_gen.h>
#include <symbol_gen.h>

p_ir_program ir_program_gen(size_t func_cnt)
{
    p_ir_program p_program = malloc(sizeof(*p_program));
    *p_program = (ir_program){
        .func_cnt = func_cnt,
        .func_table = ir_func_table_gen(func_cnt),
        .p_store = NULL,
    };
    return p_program;
}


void ir_program_drop(p_ir_program p_program)
{
    assert(p_program);
    ir_func_table_drop(p_program->func_table, p_program->func_cnt);
    symbol_store_drop(p_program->p_store);
    free(p_program);
}