# 📝 CSL

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Version](https://img.shields.io/badge/version-1.0.0-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Language](https://img.shields.io/badge/language-C-orange)

CSL (C Simple Logger) is a lightweight, flexible logging library for C applications. It provides customizable logging levels, colorized output, and extensible handlers.

## 📥 Installation

```bash
curl -o logger.h https://raw.githubusercontent.com/DilemaFixer/CSL/main/logger.h
curl -o logger.c https://raw.githubusercontent.com/DilemaFixer/CSL/main/logger.c
```

## 🔧 API and Usage Examples

### 📌 Data Types and Structures

The library defines several key data types and structures for logging functionality.

```c
/**
 * Log level enumeration
 */
typedef enum log_level {
   DEBUG,  // Most detailed level for debugging information
   INFO,   // General information messages
   WARN,   // Warning messages
   ERR,    // Error messages
   NONE    // No logging
} log_level;

/**
 * Log message structure containing all information about a log entry
 */
typedef struct log_message {
    const char* file;             // Source file where log was called
    int line;                     // Line number in source file
    log_level level;              // Severity level of the message
    const char* level_str;        // String representation of severity
    const char* color;            // ANSI color code for the level
    char* time_str;               // Formatted timestamp
    char* formatted_message;      // The actual log message text
} log_message;

/**
 * Function pointer type for custom log handlers
 */
typedef void (*log_handler_fn)(const log_message* message, void* user_data);
```

### 📌 Configuration Variables

Global configuration options that control logging behavior.

```c
/**
 * When set to true, timestamps will be included in log messages
 */
extern bool print_time_in_log;

/**
 * When set to true, file names and line numbers will be included in log messages
 */
extern bool print_where_in_log;
```

### 📌 Basic Logging Functions

Core logging macros for different severity levels.

```c
/**
 * Log a debug message
 */
#define dlog(format, ...)

/**
 * Log an informational message
 */
#define ilog(format, ...)

/**
 * Log a warning message
 */
#define wlog(format, ...)

/**
 * Log an error message and exit the program
 */
#define elog(format, ...)
```

#### Example

```c
#include "logger.h"

// Enable timestamps and file/line information
print_time_in_log = true;
print_where_in_log = true;

// Log messages at different levels
dlog("This is a debug message: %d", 42);
ilog("This is an info message");
wlog("This is a warning message about %s", "something");
elog("This is an error message that will terminate the program");
```

### 📌 Log Level Configuration

Functions to control which messages are displayed based on their severity.

```c
/**
 * Set the minimum log level that will be displayed
 */
void set_log_level(log_level level);

/**
 * Get the current minimum log level
 */
log_level get_log_level(void);
```

#### Example

```c
#include "logger.h"

// Only show warnings and errors
set_log_level(WARN);

// This won't be displayed
dlog("Debug message");
ilog("Info message");

// These will be displayed
wlog("Warning message");
elog("Error message");
```

### 📌 Custom Log Handlers

Functions to register custom callbacks for processing log messages.

```c
/**
 * Register a custom function to handle log messages
 */
bool register_log_handler(log_handler_fn handler, void* user_data, log_level min_level);

/**
 * Unregister a previously registered log handler
 */
bool unregister_log_handler(log_handler_fn handler);

/**
 * Remove all registered log handlers
 */
void clear_log_handlers(void);
```

#### Example

```c
#include "logger.h"
#include <stdio.h>

// Custom log handler that writes to a file
void file_logger(const log_message* message, void* user_data) {
    FILE* log_file = (FILE*)user_data;
    fprintf(log_file, "[%s] %s:%d - %s\n", 
            message->level_str, 
            message->file, 
            message->line, 
            message->formatted_message);
}

// Usage
FILE* log_file = fopen("application.log", "a");
register_log_handler(file_logger, log_file, INFO);

// Log some messages
ilog("This will go to both console and file");
dlog("This will only go to console if DEBUG >= global_min_level");

// Clean up
unregister_log_handler(file_logger);
fclose(log_file);
```

### 📌 Utility Functions

Helper functions for working with log levels and timestamps.

```c
/**
 * Convert a log level to its string representation
 */
const char* log_level_to_str(log_level level);

/**
 * Get the ANSI color code for a log level
 */
const char* log_level_to_color(log_level level);

/**
 * Get the current time as a formatted string
 */
char* current_time_str(void);
```

#### Example

```c
#include "logger.h"
#include <stdio.h>

// Print all available log levels
log_level levels[] = {DEBUG, INFO, WARN, ERR, NONE};
for (int i = 0; i < 5; i++) {
    printf("Level %d: %s\n", levels[i], log_level_to_str(levels[i]));
}

// Get the current time
printf("Current time: %s\n", current_time_str());
```
