#ifndef __IRSYMBOL__
#define __IRSYMBOL__

#include <ir.h>

enum ir_operand_kind {
    declared_var,
    temp_var,
    immedicate_int_val,
    immedicate_float_val,
    immedicate_void_val,
};
struct ir_operand {
    ir_operand_kind kind;
    union {
        p_ir_temp_sym p_temp_sym;
        p_symbol_sym p_sym;
        int intconst;
        float floatconst;
    };
};

#endif