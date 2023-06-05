#ifndef __IR_TEMP_SYM__
#define __IR_TEMP_SYM__

#include <ir.h>
struct ir_temp_sym {
    bool is_pointer;
    basic_type b_type;
    size_t id;

    list_head node;
};

#endif