#include "log.h"
#include <stdio.h>

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

LOG_LEVEL highestThreshold(struct LogThresholds th) {
    return ((th.console_threshold <= th.logfile_threshold) ? th.console_threshold : th.logfile_threshold);
}

void my_log(LOG_LEVEL level, const char * filename, int line, const char * function, const char * text) {
    if (level > highestThreshold(logThresholds)) {
        return;
    }
    char buffer[256];
    sprintf(buffer, "%s %s:%d (%s) %s\n", log_level_description(level), filename, line, function, text);
    if (level <= logThresholds.console_threshold) {
        printf(buffer);
    }
    if (level <= logThresholds.logfile_threshold) {
        FILE * pLogFile;
        pLogFile = fopen("./attache.log","a");
        if (pLogFile == NULL) {
            printf("Error opening file\n");
        }
        fprintf(pLogFile, buffer);
        fclose(pLogFile);
    }
}
