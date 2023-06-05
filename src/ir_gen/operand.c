
#include <ir_gen.h>
#include <ir_gen/operand.h>

#include <symbol/sym.h>
#include <symbol/type.h>



basic_type ir_operand_get_basic_type(p_ir_operand p_operand)
{
    switch (p_operand->kind) {
        case immedicate_int_val:
            return type_int;
        case immedicate_float_val:
            return type_float;
        case immedicate_void_val:
            return type_void;
        case declared_var:
            assert(p_operand->p_sym->p_type->kind != type_arrary);
            return p_operand->p_sym->p_type->basic;
        case temp_var:
            assert(!p_operand->p_temp_sym->is_pointer);
            return p_operand->p_temp_sym->b_type;
    }
}


p_ir_operand ir_operand_int_gen(int intconst)
{
    p_ir_operand p_ir_int = malloc(sizeof(*p_ir_int));
    *p_ir_int = (ir_operand){
        .intconst = intconst,
        .kind = immedicate_int_val,
    };
    return p_ir_int;
}

p_ir_operand ir_operand_float_gen(float floatconst)
{
    p_ir_operand p_ir_float = malloc(sizeof(*p_ir_float));
    *p_ir_float = (ir_operand){
        .floatconst = floatconst,
        .kind = immedicate_float_val,
    };
    return p_ir_float;
}

p_ir_operand ir_operand_void_gen(void)
{
    p_ir_operand p_ir_void = malloc(sizeof(*p_ir_void));
    *p_ir_void = (ir_operand){
        .kind = immedicate_void_val,
    };
    return p_ir_void;
}
// 已定义变量转换为操作数， 全局变量或函数存储名字， 局部变量存储 id
p_ir_operand ir_operand_declared_sym_gen(p_symbol_sym p_h_sym)
{
    p_ir_operand p_sym = malloc(sizeof(*p_sym));
    *p_sym = (ir_operand){
        .p_sym = p_h_sym,
    };
    return p_sym;
}

p_ir_operand ir_operand_copy(p_ir_operand p_operand)
{
    p_ir_operand p_new_operand = malloc(sizeof(*p_new_operand));
    *p_new_operand = *p_operand;
    return p_new_operand;
}

p_ir_operand ir_operand_temp_sym_gen(p_ir_temp_sym p_temp_sym)
{
    p_ir_operand p_sym = malloc(sizeof(*p_sym));
    *p_sym = (ir_operand){
        .kind = temp_var,
        .p_temp_sym = p_temp_sym,
    };
    return p_sym;
}


void ir_operand_drop(p_ir_operand p_operand)
{
    assert(p_operand);
    free(p_operand);
}
