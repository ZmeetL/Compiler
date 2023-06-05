#ifndef __IR_TEST_INSTR_DEFINE__
#define __IR_TEST_INSTR_DEFINE__

#include <ir.h>

#include <ir_test/memory_stack.h>

#include <util/list.h>

memory_type ir_instr_test(p_list_head p_list, memory_stack **global_stack, memory_stack **top_stack);
memory_type ir_ret_instr_test(p_ir_ret_instr p_instr, memory_stack *global_stack, memory_stack *top_stack);
void ir_binary_instr_test(ir_instr_type instr_type, p_ir_binary_instr p_instr, memory_stack *global_stack, memory_stack *top_stack);
void ir_unary_instr_test(ir_instr_type instr_type, p_ir_unary_instr p_instr, memory_stack *global_stack, memory_stack *top_stack);
void ir_array_assign_instr_test(p_ir_array_assign_instr p_instr, memory_stack *global_stack, memory_stack *top_stack);
void ir_array_instr_test(p_ir_array_instr p_instr, memory_stack *global_stack, memory_stack *top_stack);
void ir_call_instr_test(p_ir_call_instr p_instr, memory_stack **global_stack, memory_stack **top_stack);

#endif