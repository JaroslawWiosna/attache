#ifndef LOG_H
#define LOG_H

#include <string.h>

// TODO(#16): Let's make loglevels

#define LEVEL_ERROR 0
#define LEVEL_WARN 1

#define FILENAME(filepath) (strrchr(filepath, '/') ? strrchr(filepath, '/') + 1 : filepath)

#define LOG(level, text) my_log(level, FILENAME(__FILE__), __LINE__, __FUNCTION__, text)
#define LOGE(text) LOG(LEVEL_ERROR, text)
#define LOGW(text) LOG(LEVEL_WARN, text)

// TODO(#17): Filepath in logging is too long. Use filename instead
void my_log(int level, const char * filename, int line, const char * function, const char * text);

#endif // LOG_H
