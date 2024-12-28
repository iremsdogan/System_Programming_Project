// Manages process logs and writes to the log file.
#include "include/logger.h"
#include <stdio.h>
#include <time.h>

// Application Logging
void log_operation(const char *operation, const char *result) {
    FILE *log_file = fopen("log.txt", "a");
    if (!log_file){
        perror("Failed to open log file");
        return;
    } 
    time_t now = time(NULL);
    fprintf(log_file, "[%s] %s: %s\n", ctime(&now), operation, result);
    fclose(log_file);
}
