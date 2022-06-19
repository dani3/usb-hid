#ifndef LOGGER_H
#define LOGGER_H

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARNING,
    LOG_LEVEL_ERROR,
} log_level_t;

void _log_debug(const char* const format, ...);
void _log_info(const char* const format, ...);
void _log_warning(const char* const format, ...);
void _log_error(const char* const format, ...);

#define LOG_DEBUG(...) _log_debug(__VA_ARGS__);
#define LOG_INFO(...)  _log_info(__VA_ARGS__);
#define LOG_WARN(...)  _log_warning(__VA_ARGS__);
#define LOG_ERROR(...) _log_error(__VA_ARGS__);

#endif
