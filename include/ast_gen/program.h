#ifndef __AST_GEN_PROGRAM__
#define __AST_GEN_PROGRAM__

#include <ast/program.h>

p_ast_program ast_program_gen(void);
void ast_program_drop(p_ast_program p_program);

p_ast_program ast_program_func_add(p_ast_program p_program, p_ast_func p_func);

p_symbol_item ast_symbol_item_add(p_ast_program p_program, p_symbol_sym p_sym, bool is_global);
p_symbol_item ast_symbol_item_find(p_ast_program p_program, const char *name);
p_symbol_str ast_symbol_str_get(p_ast_program p_program, const char *string);

void ast_symbol_zone_push(p_ast_program p_program);
void ast_symbol_zone_pop(p_ast_program p_program);

#endif