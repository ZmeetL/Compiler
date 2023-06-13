#include <frontend/log.h>

#include <stdarg.h>
#include <util/log.h>

void frontend_log(loglevel level, YYLTYPE *yylloc, yyscan_t yyscanner, const char *format, ...) {
    const char *pos = "Line ";

    va_list args;
    va_start(args, format);
    vaLOG(level, " ", pos, format, args);
    va_end(args);
}