#include "log.h"
#include <stdio.h>

void my_log(int level, const char * filepath, int line, const char * function, const char * text) {
    static const char * marks[2] = {
        "[ERROR]",
        "[WARN]"
    };

    printf("%s %s:%d (%s) %s\n", marks[level], filepath, line, function, text);
}