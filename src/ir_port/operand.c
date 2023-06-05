#include <ir_port/operand.h>
#include <ir/operand.h>
#include <ir/temp_sym.h>

#include <symbol/sym.h>
#include <symbol/type.h>
ir_operand_kind ir_operand_get_kind(p_ir_operand p_operand)
{
    return p_operand->kind;
}

static inline bool ir_operand_can_get_name(p_ir_operand p_operand)
{
    return (p_operand->kind == declared_var && (p_operand->p_sym->is_global || p_operand->p_sym->p_type->kind == type_func));
}

// 函数、全局变量使用名字
char* ir_operand_get_sym_name(p_ir_operand p_operand)
{
    assert(ir_operand_can_get_name(p_operand));
    return p_operand->p_sym->name;
}
// 局部、临时变量使用 id
size_t ir_operand_get_sym_id(p_ir_operand p_operand)
{
    assert(!ir_operand_can_get_name(p_operand));
    if(p_operand->kind == temp_var)
        return p_operand->p_temp_sym->id;
    else 
        return p_operand->p_sym->id;
}

int ir_operand_get_int(p_ir_operand p_operand)
{
    return p_operand->intconst;
}
float ir_operand_get_float(p_ir_operand p_operand)
{
    return p_operand->floatconst;
}