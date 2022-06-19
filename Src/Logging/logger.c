#include "logger.h"
#include "stm32f1xx.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

static log_level_t s_system_log_level;

/**
 * \brief Redirects `printf()` output to the serial wire out (SWO).
 * This function overrides a `weak` function symbol and is not to be used directly.
 */
static int _write(int file, char* ptr, int len) {
    for (int i = 0; i < len; ++i) {
        ITM_SendChar(*ptr++);
    }

    return len;
}

static const char* const _get_log_level_string(log_level_t level) {
    switch (level) {
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_WARNING:
            return "WARNING";
        case LOG_LEVEL_ERROR:
            return "ERROR";
    }

    return "UNKNOWN";
}

static void _log(log_level_t log_level, const char* const format, va_list args) {
    if (log_level > s_system_log_level) {
        return;
    }

    printf("[%s] ", _get_log_level_string(log_level));
    vfprintf(stdout, format, args);
    printf("\n");
}

void _log_debug(const char* const format, ...) {
    va_list args;
    va_start(args, format);
    _log(LOG_LEVEL_DEBUG, format, args);
    va_end(args);
}

void _log_info(const char* const format, ...) {
    va_list args;
    va_start(args, format);
    _log(LOG_LEVEL_INFO, format, args);
    va_end(args);
}

void _log_warning(const char* const format, ...) {
    va_list args;
    va_start(args, format);
    _log(LOG_LEVEL_WARNING, format, args);
    va_end(args);
}

void _log_error(const char* const format, ...) {
    va_list args;
    va_start(args, format);
    _log(LOG_LEVEL_ERROR, format, args);
    va_end(args);
}

/**
 * \brief Log the content of an array.
 *
 * \param label The label of the array.
 * \param array Pointer to the array.
 * \param len The length of data in bytes.
 */
void log_debug_array(const char* const label, const void* array, uint16_t len) {
    if (LOG_LEVEL_DEBUG > s_system_log_level)
        return;

    printf("[%s] %s[%d]: {", _get_log_level_string(LOG_LEVEL_DEBUG), label, len);
    for (uint16_t i = 0; i < len; i++) {
        uint8_t val = *((uint8_t*) (array + i));
        printf("0x%02X", val);

        // Add ", " after all elements except the last one.
        if (i < len - 1) {
            printf(", ");
        }
    }
    printf("}\n");
}
