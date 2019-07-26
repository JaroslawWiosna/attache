#include "log.h"
#include <stdio.h>

// TODO(#27): create function that returns the highest threshold
struct LogThresholds logThresholds = { .console_threshold = LEVEL_ERROR, .logfile_threshold = LEVEL_DEBUG };

const char * log_level_description(LOG_LEVEL level) {
    switch(level) {
        case LEVEL_ERROR:
            return "[ ERROR ]";
        case LEVEL_WARN:
            return "[  WARN ]";
        case LEVEL_INFO:
            return "[  INFO ]";
        case LEVEL_DEBUG:
            return "[ DEBUG ]";
        case LOG_LEVEL_SIZE:
        default:
            LOGE("Fatal error");
            return "(null)";
    }
}

void my_log(LOG_LEVEL level, const char * filename, int line, const char * function, const char * text) {



    if (level <= logThresholds.console_threshold) {
        printf("%s %s:%d (%s) %s\n", log_level_description(level), filename, line, function, text);
    }

    // TODO(#28): append log to logfile
}
