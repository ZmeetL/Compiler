#include <ir_gen/func.h>
#include <ir_gen.h>

p_ir_func ir_func_table_gen(size_t cnt){
    p_ir_func p_func = malloc(sizeof(*p_func) * cnt);
    for (size_t i = 0; i < cnt; ++i) {
        p_func[i] = (ir_func){
            .entry_block = list_head_init(&(p_func + i)->entry_block),
            .temp_sym_head = list_head_init(&(p_func + i)->temp_sym_head),
        };
    }
    return p_func;
}

void ir_func_add_basic_block(p_ir_func p_func, p_ir_basic_block p_basic_block)
{
    list_add_prev(&p_basic_block->node, &p_func->entry_block);
}

void ir_func_temp_sym_add(p_ir_func p_func, p_ir_temp_sym p_temp_sym)
{
    list_add_prev(&p_temp_sym->node, &p_func->temp_sym_head);
}

void ir_func_set_block_id(p_ir_func p_func)
{
    size_t id = 0;
    p_list_head p_node;
    list_for_each(p_node, &p_func->entry_block){
        p_ir_basic_block p_basic_block = list_entry(p_node, ir_basic_block, node);
        p_basic_block->block_id = id ++;
    }
}

void ir_func_set_temp_id(p_ir_func p_func)
{
    p_list_head p_node;
    size_t id = 0;
    list_for_each(p_node, &p_func->temp_sym_head){
        p_ir_temp_sym p_temp_sym = list_entry(p_node, ir_temp_sym, node);
        p_temp_sym->id = id ++;
    }
}

void ir_func_table_drop(p_ir_func p_func, size_t cnt)
{
    for (size_t i = 0; i < cnt; ++i) {
        while (!list_head_alone(&(p_func + i)->entry_block)) {
            p_ir_basic_block p_del = list_entry((p_func + i)->entry_block.p_next, ir_basic_block, node);
            list_del(&p_del->node);
            ir_basic_block_drop(p_del);
        }
        while(!list_head_alone(&(p_func + i)->temp_sym_head))
        {
            p_ir_temp_sym p_temp_sym = list_entry((p_func + i)->temp_sym_head.p_next, ir_temp_sym, node);
            list_del(&p_temp_sym->node);
            free(p_temp_sym);
        }
    }
    free(p_func);
}