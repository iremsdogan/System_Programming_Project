// Performs file operations (read, write, copy, move, **create)
#include "include/file_operations.h"
#include "include/logger.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

// File Copying
void copy_file(const char *src, const char *dest){
    int src_fd = open(src, O_RDONLY);
    if(src_fd<0){
        perror("Failed to open source file");
        log_operation("copy_file", "Failed to open source file");
        return ;
    }
    int dest_fd = creat(dest, 0644);
    if(dest_fd<0){
        perror("Failed to create destination file");
        close(src_fd);
        log_operation("copy_file", "Failed to create destination file");
        return;
    }
    char buffer[1024];
    ssize_t bytes;
    while((bytes = read(src_fd, buffer, sizeof(buffer))) > 0){
        write(dest_fd, buffer, bytes);
    }
    close(src_fd);
    close(dest_fd);

    printf("File copied succesfully from %s to %s\n", src, dest);
    log_operation("copy_file", "File copied successfully");
}
// File Deletion
void remove_file(const char *path){
    if(unlink(path) < 0){
        perror("Failed to remove file");
        log_operation("remove_file", "Failed to remove file");
    }
    else{
        printf("File %s removed succesfully. \n", path);
        log_operation("remove_file", "File removed successfully");
    }
}
// File reading
void read_file(const char *path){
    int fd = open(path, O_RDONLY);
    if(fd < 0){
        perror("Failed to open file for reading");
        log_operation("read_file", "Failed to open file for reading");
        return;
    }

    char buffer[1024];
    ssize_t bytes;
    while((bytes = read(fd, buffer, sizeof(buffer))) > 0){
        write(STDOUT_FILENO, buffer, bytes);
    }

    printf("\n");
    close(fd);
    log_operation("read_file", "File read successfully");
}
// File writing
void write_file(const char *path) {
    char content[1024];
    printf("Enter content to write to the file: ");
    getchar();
    fgets(content, sizeof(content), stdin);

    int fd = open(path, O_WRONLY | O_APPEND);
    if (fd < 0) {
        perror("Failed to open file for writing");
        log_operation("write_file", "Failed to open file for writing");
        return;
    }

    if (write(fd, content, strlen(content)) < 0) {
        perror("Failed to write to the file");
        log_operation("write_file", "Failed to write to the file");
    } else {
        printf("Content written to %s successfully.\n", path);
        log_operation("write_file", "Content written successfully");
    }

    close(fd);
}
// File moving
void move_file(const char *src, const char *dest){
    if(rename(src, dest) < 0){
        perror("Failed to move file");
        log_operation("move_file", "Failed to move file");
    }
    else{
        printf("File moved succesfully from %s to %s\n", src, dest);
        log_operation("move_file", "File moved successfully");
    }
}

// File creating
void create_file(const char *path){

    char content[1024];

    printf("Enter initial content for the file (press Enter for empty file): ");
    getchar();
    fgets(content, sizeof(content), stdin);

    int fd = creat(path, 0644);
    if(fd<0){
        perror("Failed to create file");
        log_operation("create_file", "Failed to create file");
        return;
    }

    if(strlen(content) > 1){
        if(write(fd, content, strlen(content)) < 0){
            perror("Failed to write initial content to the file");
            log_operation("create_file", "Failed to write initial content to the file");
            close(fd);
            return;
        }
    }

    close(fd);
    printf("File %s created succesfully.\n", path);
    log_operation("create_file", "File created successfully");
}

// File renaming
void rename_file(const char *old_name, const char *new_name){
    if(rename(old_name, new_name) < 0){
        perror("Failed to rename file");
        log_operation("rename_file", "Failed to rename file");
    }
    printf("File renamed successfully from %s to %s\n", old_name, new_name);    
    log_operation("rename_file", "File renamed successfully");
    
}

// File searching
void search_files(const char *dir_path, const char *search_term){
    DIR *dir = opendir(dir_path);
    if(dir == NULL){
        perror("Failed to open directory");
        log_operation("search_files", "Failed to open directory");
        return;
    }
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL){
        if(strstr(entry->d_name, search_term) != NULL){
            printf("Found: %s\n", entry->d_name);
        }
    }
    closedir(dir);
    log_operation("search_files", "Search completed");
}

// File display
void display_file(const char *path){
    int fd = open(path, O_RDONLY);
    if(fd < 0){
        perror("Failed to open file for display");
        log_operation("display_file", "Failed to open file for display");
        return;
    }

    char buffer[1024];
    ssize_t bytes;
    while((bytes = read(fd, buffer, sizeof(buffer))) > 0){
        write(STDOUT_FILENO, buffer, bytes);
    }

    printf("\n");
    close(fd);
    log_operation("display_file", "File displayed successfully");
}