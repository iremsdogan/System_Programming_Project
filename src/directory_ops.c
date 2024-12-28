// Contains functions for listing, creating, and deleting folders.
#include "include/directory_ops.h"
#include "include/logger.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

void print_file_info(const char *path, const struct dirent *entry) {
    struct stat file_stat;
    char full_path[1024];

    // Generate the full file path
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    // Get File Info
    if (stat(full_path, &file_stat) < 0) {
        perror("Failed to get file information");
        return;
    }

    // File type
    char type = '-';
    if (S_ISDIR(file_stat.st_mode)) type = 'd';
    else if (S_ISLNK(file_stat.st_mode)) type = 'l';
    else if (S_ISCHR(file_stat.st_mode)) type = 'c';
    else if (S_ISBLK(file_stat.st_mode)) type = 'b';

    // Permissions
    char permissions[10] = "---------";
    if (file_stat.st_mode & S_IRUSR) permissions[0] = 'r';
    if (file_stat.st_mode & S_IWUSR) permissions[1] = 'w';
    if (file_stat.st_mode & S_IXUSR) permissions[2] = 'x';
    if (file_stat.st_mode & S_IRGRP) permissions[3] = 'r';
    if (file_stat.st_mode & S_IWGRP) permissions[4] = 'w';
    if (file_stat.st_mode & S_IXGRP) permissions[5] = 'x';
    if (file_stat.st_mode & S_IROTH) permissions[6] = 'r';
    if (file_stat.st_mode & S_IWOTH) permissions[7] = 'w';
    if (file_stat.st_mode & S_IXOTH) permissions[8] = 'x';

    // Owner and Group Information
    struct passwd *pw = getpwuid(file_stat.st_uid);
    struct group *gr = getgrgid(file_stat.st_gid);

    // File Size and Last Modified Date
    char time_buf[64];
    strftime(time_buf, sizeof(time_buf), "%b %d %H:%M", localtime(&file_stat.st_mtime));

    // Print File Information
    printf("%c%s    %3ld   %8s     %8s   %8ld  %s   %s\n",
           type, permissions, file_stat.st_nlink,
           pw ? pw->pw_name : "?", gr ? gr->gr_name : "?",
           file_stat.st_size, time_buf, entry->d_name);
}

// Folder Listing
void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Failed to open directory");
        log_operation("list_directory", "Failed to open directory");
        return;
    }

    struct dirent *entry;
    printf("---------------------------------------------------------------------------\n");
    while ((entry = readdir(dir)) != NULL) {
        print_file_info(path, entry);
    }

    closedir(dir);
    log_operation("list_directory", "Directory listed successfully");
}

// Folder Creation
void create_directory(const char *path){
    if(mkdir(path, 0755) < 0){
        perror("Failed to create directory");
        log_operation("create_directory", "Failed to create directory");
    }
    else{
        printf("created successfully.\n");
        log_operation("create_directory", "Directory created successfully");
    }
}

// Folder Deletion
void remove_directory(const char *path){
    if (rmdir(path) < 0) {
        if (errno == ENOTEMPTY) {
            char response;
            printf("Directory %s is not empty. Do you want to remove it and all its contents? (y/n): ", path);
            scanf(" %c", &response);

            if (response == 'y' || response == 'Y') {
                remove_directory_with_content(path);
            } else {
                printf("Directory %s was not removed.\n", path);
                log_operation("remove_directory", "Directory not removed by user choice");
            }
        } else {
            perror("Failed to remove directory");
            log_operation("remove_directory", "Failed to remove directory");
        }
    } else {
        printf("Directory %s removed successfully.\n", path);
        log_operation("remove_directory", "Directory removed successfully");
    }
}

// Force Folder Deletion 
void remove_directory_with_content(const char *path){
    DIR *dir = opendir(path);
    if (!dir) {
        perror("Failed to open directory");
        log_operation("remove_directory_with_content", "Failed to open directory");
        return;
    }

    struct dirent *entry;
    char filepath[1024];

    while ((entry = readdir(dir)) != NULL) {
        // Skip . and .. directories
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Create the full path
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
        struct stat statbuf;

        if (stat(filepath, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                // Recursively remove subdirectories
                remove_directory_with_content(filepath);
            } else {
                // Remove file
                if (unlink(filepath) < 0) {
                    perror("Failed to remove file");
                    log_operation("remove_directory_with_content", "Failed to remove file");
                }
            }
        }
    }

    closedir(dir);

    // Remove the directory itself
    if (rmdir(path) < 0) {
        perror("Failed to remove directory");
        log_operation("remove_directory_with_content", "Failed to remove directory");
    } else {
        printf("Directory %s and its content removed successfully.\n", path);
        log_operation("remove_directory_with_content", "Directory and its content removed successfully");
    }
}
