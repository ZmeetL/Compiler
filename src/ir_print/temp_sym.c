#include <ir_print.h>
#include <ir/temp_sym.h>

#include <stdio.h>
void ir_temp_sym_print(p_ir_temp_sym p_temp_sym)
{
    assert(p_temp_sym);
    if(p_temp_sym->is_pointer)
    {
        printf("[ 0 X ");
        ir_basic_type_print(p_temp_sym->b_type);
        printf("]* %%t%ld ", p_temp_sym->id);    
    }
    else {
        ir_basic_type_print(p_temp_sym->b_type);
        printf(" %%t%ld ", p_temp_sym->id);
    }
}