#include <frontend.h>

#include <frontend/lexer.h>
#include <frontend/parser.h>

p_ast_program frontend_trans(const char *file_name) {
    printf("=== lexical analysis begin ===\n");
    yyscan_t scanner;
    extra_info extra = (extra_info) {
        .fs = NULL,
        .p_ast = NULL,
    };
    yylex_init_extra(&extra, &scanner);
    frontend_push_file(file_name, NULL, &extra, scanner);

    yyparse(scanner);
    p_ast_program p_ast = yyget_extra(scanner)->p_ast;

    yylex_destroy(scanner);
    printf("=== lexical analysis end ===\n");
    return p_ast;
}