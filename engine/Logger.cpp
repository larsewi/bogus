//
// Created by larsewi on 31.08.2020.
//

#include "Logger.h"

void logger::log_f(
        const char *file, const char *func, int line,
        const char *type, const char *color, FILE *filePtr,
        const char *format, ...
) {
    va_list ap;
    va_start(ap, format);

    fprintf(filePtr, "[%s%s%s][%s:%d in %s]: ", color, type, LOGGER_CLEAR_COLOR, file, line, func);
    vfprintf(filePtr, format, ap);
    fprintf(filePtr, "\n");

    va_end(ap);
}