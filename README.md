# CSL
# Simple C Logger Library
A lightweight, colorful logging library for C applications.

## Features
- Four log levels: DEBUG, INFO, WARNING, and ERROR
- Colored output for better readability
- Optional timestamp display
- Optional file name and line number information
- Easy to integrate into any C project

## Usage
Include the header file in your source:

```c
#include "logger.h"
```

Configure the logger:

```c
// Enable timestamp display
print_time_in_log = true;

// Enable file/line information
print_where_in_log = true;
```

Log messages at different levels:

```c
dlog("Debug message");
ilog("Information message with value: %d", 42);
wlog("Warning message");
elog("Error message: %s", "File not found");
```

## Examples

### Basic Usage

```c
#include "logger.h"

int main() {
    // Enable file/line information in logs
    print_where_in_log = true;
    
    // Log messages at different levels
    dlog("Starting application");
    ilog("User logged in: %s", "john_doe");
    wlog("Disk space low: %d%% used", 85);
    elog("Connection failed to %s", "database");
    
    return 0;
}
```

### With Timestamps

```c
#include "logger.h"

int main() {
    // Enable timestamps and location info
    print_time_in_log = true;
    print_where_in_log = true;
    
    ilog("Application initialized with timestamps");
    
    // Perform some operations
    for (int i = 0; i < 3; i++) {
        dlog("Processing item %d", i);
    }
    
    ilog("Processing complete");
    return 0;
}
```

### Error Handling

```c
#include "logger.h"

int divide(int a, int b) {
    if (b == 0) {
        elog("Division by zero attempted: %d / %d", a, b);
        return -1;
    }
    
    dlog("Performing division: %d / %d", a, b);
    return a / b;
}

int main() {
    print_where_in_log = true;
    
    int result = divide(10, 2);
    if (result >= 0) {
        ilog("Division result: %d", result);
    }
    
    result = divide(5, 0);
    if (result < 0) {
        wlog("Division failed");
    }
    
    return 0;
}
```

## Compilation

```bash
gcc -c logger.c -o logger.o
gcc your_app.c logger.o -o your_app
```

## License
MIT License
