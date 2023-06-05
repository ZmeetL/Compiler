#ifndef __IR_TEST_OPERAND_DEFINE__
#define __IR_TEST_OPERAND_DEFINE__

#include <ir_test/memory_stack.h>

#include <ir.h>

memory_type ir_operand_data_get(p_ir_operand p_operand, const memory_stack *global_stack, const memory_stack *stack);

#endif