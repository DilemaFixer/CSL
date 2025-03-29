# Enhanced C Logging System

A flexible, lightweight, and extensible logging system for C applications with support for custom handlers, colored console output, and multiple log levels.

## Features

- 📊 Multiple log levels (DEBUG, INFO, WARN, ERROR)
- 🎨 Colored terminal output for better readability
- 📝 Configurable formatting with file name, line number, and timestamp
- 🔌 Custom handler support for extending functionality
- 📂 Easily integrate with file logging, network logging, or custom destinations
- 🚀 Simple macro interface for easy usage
- 🛡️ Handles variadic arguments safely

## Installation

### Option 1: Download directly into your project

Copy these commands to download just the logger files into your project:

```bash
# Download the header file
curl -o logger.h https://raw.githubusercontent.com/DilemaFixer/CSL/main/logger.h

# Download the implementation file
curl -o logger.c https://raw.githubusercontent.com/DilemaFixer/CSL/main/logger.c
```

### Option 2: Clone the entire repository

```bash
git clone https://github.com/DilemaFixer/CSL.git
```

## Basic Usage

```c
#include "logger.h"

int main() {
    // Enable timestamp and source file location in logs
    print_time_in_log = true;
    print_where_in_log = true;
    
    // Log at different levels
    dlog("This is a debug message");
    ilog("This is an info message");
    wlog("This is a warning message");
    elog("This is an error message that will terminate the program");
    
    return 0;
}
```

## Advanced Usage

### Custom Log Handlers

You can register your own log handlers to process log messages:

```c
// Example: Custom handler to write logs to a file
void file_logger(const log_message* message, void* user_data) {
    FILE* log_file = (FILE*)user_data;
    fprintf(log_file, "[%s] [%s:%d] %s: %s\n", 
            message->time_str, 
            message->file, 
            message->line,
            message->level_str, 
            message->formatted_message);
    fflush(log_file);
}

int main() {
    // Open a log file
    FILE* log_file = fopen("application.log", "a");
    
    // Register custom file logger for INFO and above
    register_log_handler(file_logger, log_file, INFO);
    
    // Your application code here...
    ilog("Application started");
    
    // Clean up
    fclose(log_file);
    return 0;
}
```

### Setting Global Log Level

Control which messages get processed:

```c
// Only show warnings and errors
set_log_level(WARN);

dlog("This will not be displayed"); // Filtered out
ilog("This will not be displayed"); // Filtered out
wlog("This will be displayed");     // Shown
elog("This will be displayed");     // Shown and will exit
```

## API Reference

### Log Levels

```c
typedef enum log_level {
   DEBUG,  // Detailed information for debugging
   INFO,   // General information messages
   WARN,   // Warning conditions
   ERR,    // Error conditions (terminates program)
   NONE    // Disable all logging
} log_level;
```

### Logging Macros

```c
// Debug level logs
dlog(format, ...);

// Information level logs
ilog(format, ...);

// Warning level logs
wlog(format, ...);

// Error level logs (terminates program)
elog(format, ...);
```

### Handler Management

```c
// Register a custom log handler
bool register_log_handler(log_handler_fn handler, void* user_data, log_level min_level);

// Unregister a handler
bool unregister_log_handler(log_handler_fn handler);

// Remove all handlers
void clear_log_handlers(void);
```

### Configuration

```c
// Enable/disable timestamp in logs
extern bool print_time_in_log;

// Enable/disable file and line number in logs
extern bool print_where_in_log;

// Set minimum log level globally
void set_log_level(log_level level);

// Get current log level
log_level get_log_level(void);
```

## Example Handlers

### Network Logger

```c
void network_logger(const log_message* message, void* user_data) {
    int socket_fd = *(int*)user_data;
    
    char buffer[2048];
    snprintf(buffer, sizeof(buffer), "[%s] [%s] %s\n", 
             message->time_str, 
             message->level_str, 
             message->formatted_message);
             
    send(socket_fd, buffer, strlen(buffer), 0);
}
```

### Database Logger

```c
void db_logger(const log_message* message, void* user_data) {
    db_connection* db = (db_connection*)user_data;
    
    // Prepare a statement to insert the log
    const char* query = "INSERT INTO logs (timestamp, level, source, message) VALUES (?, ?, ?, ?)";
    
    // Execute query with parameters
    // This is pseudo-code; adapt to your database library
    db_execute(db, query, 
               message->time_str, 
               message->level_str, 
               message->file, 
               message->formatted_message);
}
```

## License

```MIT License

Copyright (c) 2025

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.```
