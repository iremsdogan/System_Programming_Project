// Checks and changes file and folder permissions.
#include "include/permissions.h"
#include "include/logger.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

void change_permissions(const char *path, mode_t mode) {
    if (chmod(path, mode) < 0) {
        perror("Failed to change permissions");
        log_operation("change_permissions", "Failed to change permissions");
    }
    else {
        char result[256];
        sprintf(result, "Permissions of %s changed to %o successfully.", path, mode);
        printf("Permissions of %s changed to %o successfully.\n", path, mode);
        log_operation("change_permissions", "Permissions changed successfully");
    }
}
