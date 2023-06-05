#include <ir_port/program.h>
#include <ir/program.h>

#include <symbol/store.h>
p_list_head ir_program_get_global_list(p_ir_program p_program)
{
    return &p_program->p_store->variable;
}

p_ir_func ir_program_get_func_table(p_ir_program p_program)
{
    return p_program->func_table;
}