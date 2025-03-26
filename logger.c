#include "logger.h"
#include <stdarg.h>

bool print_time_in_log = false;
bool print_where_in_log = false;

const char *log_level_to_str(log_level level) {
  switch (level) {
  case DEBUG:
    return "DEBUG";
  case INFO:
    return "INFO";
  case WARN:
    return "WARN";
  case ERR:
    return "ERROR";
  default:
    return "UNKNOWN";
  }
}

const char *log_level_to_color(log_level level) {
  switch (level) {
  case DEBUG:
    return BLUE;
  case INFO:
    return GREEN;
  case WARN:
    return YELLOW;
  case ERR:
    return RED;
  default:
    return RESET;
  }
}

char *current_time_str(void) {
  static char time_str[64];
  time_t now = time(NULL);
  struct tm *time_info = localtime(&now);
  strftime(time_str, sizeof(time_str), LOG_TIME_PATTERN, time_info);
  return time_str;
}

void logger(const char *file, int line, log_level level, const char *format,
            ...) {
  const char *color = log_level_to_color(level);
  printf("%s[%s]%s ", color, log_level_to_str(level), RESET);
  if (print_time_in_log) {
    printf("[%s] ", current_time_str());
  }
  if (print_where_in_log) {
    printf("[%s:%d] ", file, line);
  }
  printf(": ");
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n");
}
