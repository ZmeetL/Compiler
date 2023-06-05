#include <ir_gen.h>
#include <ir/temp_sym.h>
p_ir_temp_sym ir_temp_sym_basic_gen(basic_type b_type, p_ir_func p_func)
{
    p_ir_temp_sym p_temp_sym = malloc(sizeof(*p_temp_sym));
    *p_temp_sym = (ir_temp_sym){
        .b_type = b_type,
        .is_pointer = false,
        .node = list_head_init(&p_temp_sym->node),
    };
    ir_func_temp_sym_add(p_func, p_temp_sym);
    return p_temp_sym;
}

p_ir_temp_sym ir_temp_sym_pointer_gen(basic_type b_type, p_ir_func p_func)
{
    p_ir_temp_sym p_temp_sym = malloc(sizeof(*p_temp_sym));
    *p_temp_sym = (ir_temp_sym){
        .b_type = b_type,
        .is_pointer = true,
        .node = list_head_init(&p_temp_sym->node),
    };
    ir_func_temp_sym_add(p_func, p_temp_sym);
    return p_temp_sym;
}

void ir_temp_sym_drop(p_ir_temp_sym p_temp_sym)
{
    free(p_temp_sym);
}