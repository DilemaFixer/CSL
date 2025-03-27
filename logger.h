#ifndef LOGGER_H
#define LOGGER_H

// You can copy code to your project from
// https://github.com/DilemaFixer/CSL

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

#define RESET   "\x1b[0m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"

#define LOG_TIME_PATTERN "%d.%m.%Y %H:%M:%S"

extern bool print_time_in_log;
extern bool print_where_in_log;

typedef enum log_level {
   DEBUG,
   INFO,
   WARN,
   ERR
} log_level;

void logger(const char* file, int line, log_level level, const char* format, ...);

#define dlog(format, ...) logger(__FILE__, __LINE__, DEBUG, format, ##__VA_ARGS__)
#define ilog(format, ...) logger(__FILE__, __LINE__, INFO, format, ##__VA_ARGS__)
#define wlog(format, ...) logger(__FILE__, __LINE__, WARN, format, ##__VA_ARGS__)
#define elog(format, ...) do { \
    logger(__FILE__, __LINE__, ERR, format, ##__VA_ARGS__); \
    exit(1); \
} while(0)

#pragma GCC diagnostic pop
#endif
