#include <ir_print.h>
#include <ir/func.h>
#include <ir/basic_block.h>

#include <ir/instr.h>// 包含问题？
#include <stdio.h>

#include <symbol/sym.h>
#include <symbol/type.h>

void ir_func_print(p_ir_func p_func)
{
    assert(p_func);
    printf("define ");
    ir_symbol_type_print(p_func->p_func_sym->p_type);
    printf("%s (", p_func->p_func_sym->name);
    p_list_head p_node;
    p_symbol_type p_param_type = p_func->p_func_sym->p_type->p_params;
    list_for_each(p_node, &p_func->p_func_sym->variable) {
        if (!p_param_type) break;
        p_symbol_sym p_sym = list_entry(p_node, symbol_sym, node);
        ir_symbol_type_print(p_sym->p_type);
        printf("%%l%ld", p_sym->id);
        p_param_type = p_param_type->p_params;
        if(p_param_type)printf(", ");
    }
    printf(")\n");

    if (list_head_alone(&p_func->entry_block)) return;
    printf("{\n");
    p_param_type = p_func->p_func_sym->p_type->p_params;
    list_for_each(p_node, &p_func->p_func_sym->variable) {
        if (!p_param_type) break;
        p_symbol_sym p_sym = list_entry(p_node, symbol_sym, node);
        printf("param ");
        ir_symbol_type_print(p_sym->p_type);
        printf("%%l%ld\n", p_sym->id);
        p_param_type = p_param_type->p_params;
    }

    while (p_node != &p_func->p_func_sym->variable) {
        p_symbol_sym p_sym = list_entry(p_node, symbol_sym, node);
        printf("local ");
        ir_symbol_type_print(p_sym->p_type);
        printf("%%l%ld\n", p_sym->id);
        p_node = p_node->p_next;
    }

    list_for_each(p_node, &p_func->entry_block){
        p_ir_basic_block p_basic_block = list_entry(p_node, ir_basic_block, node);
        ir_basic_block_print(p_basic_block);
    }
    printf("}\n");
}