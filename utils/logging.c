#include "logging.h"

char* fill_string(char* string, const char *input, size_t size) {
    memset(string, '\0', size);
    memcpy(string, input, strlen(input));
    string[size - 1] = '\0';
    return string;
}


log_level_t g_level = LOG_QUIET;

void set_log_level(log_level_t level) { g_level = level; }
