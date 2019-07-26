#ifndef LOG_H
#define LOG_H

#include <string.h>
#include <stdio.h>

typedef enum {
    LEVEL_ERROR = 0,
    LEVEL_WARN,
    LEVEL_INFO,
    LEVEL_DEBUG,

    LOG_LEVEL_SIZE
} LOG_LEVEL;

struct LogThresholds {
    LOG_LEVEL console_threshold;
    LOG_LEVEL logfile_threshold;
};

extern struct LogThresholds LogThresholds;

const char * log_level_description(LOG_LEVEL level);

#define FILENAME(filepath) (strrchr(filepath, '/') ? strrchr(filepath, '/') + 1 : filepath)

#define LOG(level, text) my_log(level, FILENAME(__FILE__), __LINE__, __FUNCTION__, text)
#define LOGE(text) LOG(LEVEL_ERROR, text)
#define LOGW(text) LOG(LEVEL_WARN, text)
#define LOGI(text) LOG(LEVEL_INFO, text)
#define LOGD(text) LOG(LEVEL_DEBUG, text)

#define LOG_BUFFER_SIZE 256
char LOG_BUFFER[LOG_BUFFER_SIZE];

#define SLOG(level, text, ...) {\
    sprintf((LOG_BUFFER), (text), ##__VA_ARGS__); \
    LOG(level, LOG_BUFFER); \
}

#define SLOGW(text, ...) SLOG((LEVEL_ERROR), (text), ##__VA_ARGS__)
#define SLOGE(text, ...) SLOG((LEVEL_WARN), (text), ##__VA_ARGS__)
#define SLOGI(text, ...) SLOG((LEVEL_INFO), (text), ##__VA_ARGS__)
#define SLOGD(text, ...) SLOG((LEVEL_DEBUG), (text), ##__VA_ARGS__)

void my_log(LOG_LEVEL level, const char * filename, int line, const char * function, const char * text);

#endif // LOG_H
