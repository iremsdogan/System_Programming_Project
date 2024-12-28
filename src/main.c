// Controls the flow of the main program.
// Receives commands from the user and calls the relevant module.
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/file_operations.h"
#include "include/directory_ops.h"
#include "include/permissions.h"
#include "include/logger.h"

// print menu
void print_help() {
    printf("Available commands:\n");
    printf("  slist          - List the contents of a directory\n");
    printf("  scopy          - Copy a file\n");
    printf("  sremove        - Remove a file\n");
    printf("  swrite         - Write to a file\n");
    printf("  sread          - Read a file\n");
    printf("  smove          - Move a file\n");
    printf("  screate        - Create a file\n");
    printf("  srename        - Rename a file\n");
    printf("  ssearch        - Search for files in a directory\n");
    printf("  sdisplay       - Display the content of a file\n");
    printf("  smkdir         - Create a directory\n");
    printf("  srmdir         - Remove a directory\n");
    printf("  srmdirforce    - Remove a directory with its content\n");
    printf("  schmod         - Change permissions of a file or directory\n");
    printf("  shelp          - Show this help menu\n");
    printf("  sexit          - Exit the program\n");
}

// exit the program
void go_exit(){
    printf("Exiting the program...\n");
    exit(0);
}

int main(){
    char command[256];
    char path1[256];
    char path2[256];
    char filename[256];
    char foldername[256];
    char new_filename[256];
    char search_term[256];

    printf("** Welcome to the File Management CLI **\n");
    print_help();

    printf("Enter a command: ");
    while(scanf("%s", command) != EOF){ // end of file
        // File Operations
        // list all file and folders
        if(strcmp(command, "slist") == 0){
            
            printf("Enter the directory path to list: ");
            scanf("%255s", path1);
            list_directory(path1);
        }
        // copy file
        else if(strcmp(command, "scopy") == 0){
            printf("Enter the source file path: ");
            scanf("%255s", path1); // get source file path

            printf("Enter the source file name: ");
            scanf("%255s", filename); // get source file name

            printf("Enter the destination path: ");
            scanf("%255s", path2); // get destination file path

            char src_path[512];
            snprintf(src_path, sizeof(src_path), "%s/%s", path1, filename);
            
            char dest_path[512];
            snprintf(dest_path, sizeof(dest_path), "%s/%s", path2, filename);
            copy_file(src_path, dest_path);
        }
        // remove file
        else if(strcmp(command, "sremove") == 0){
            printf("Enter the file path to remove: ");
            scanf("%255s", path1);
            remove_file(path1);
        }
        // write into file
        else if(strcmp(command, "swrite") == 0){
            printf("Enter the file path to write: ");
            scanf("%255s", path1);
            write_file(path1);
        }
        // read a file
        else if(strcmp(command, "sread") == 0){
            printf("Enter the file path to read: ");
            scanf("%255s", path1);
            read_file(path1);
        }
        // move a file
        else if(strcmp(command, "smove") == 0){
            printf("Enter the source file path: ");
            scanf("%255s", path1);

            printf("Enter the file name: ");
            scanf("%255s", filename); 

            printf("Enter the destination path: ");
            scanf("%255s", path2);

            char src_path[512];
            snprintf(src_path, sizeof(src_path), "%s/%s", path1, filename);

            char dest_path[512];
            snprintf(dest_path, sizeof(dest_path), "%s/%s", path2, filename);
            
            move_file(src_path, dest_path);
        }
        // create a file
        else if(strcmp(command, "screate") == 0){
            printf("Enter the directory path to create the file in: ");
            scanf("%255s", path1);

            printf("Enter the file name to be created: ");
            scanf("%255s", filename); 
            
            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path1, filename);
            create_file(full_path);
        }
        // rename a file
        else if(strcmp(command, "srename") == 0){
            printf("Enter the directory path of the file to rename: ");
            scanf("%255s", path1);

            printf("Enter the current file name: ");
            scanf("%255s", filename);

            printf("Enter the new file name: ");
            scanf("%255s", new_filename);

            char old_path[512];
            snprintf(old_path, sizeof(old_path), "%s/%s", path1, filename);

            char new_path[512];
            snprintf(new_path, sizeof(new_path), "%s/%s", path1, new_filename);
            
            rename_file(old_path, new_path);
        }
        // search for a file in a directory
        else if(strcmp(command, "ssearch") == 0){
            printf("Enter the directory path to search: ");
            scanf("%255s", path1);

            printf("Enter the search term: ");
            scanf("%255s", search_term);

            search_files(path1, search_term);
        }
        // see inside a file
        else if (strcmp(command, "sdisplay") == 0) { 
            printf("Enter the file path to display: ");
            scanf("%255s", path1);
            display_file(path1);
        } 
        // Directory Operations
        // create a folder
        else if(strcmp(command, "smkdir") == 0){
            printf("Enter the folder path to create: ");
            scanf("%255s", path1);

            printf("Enter the folder name to be created: ");
            scanf("%255s", foldername); 

            char full_path[1024];
            snprintf(full_path, sizeof(full_path), "%s/%s", path1, foldername);

            printf("Directory %s ", foldername);
            create_directory(full_path);
        }
        // remove a folder but warns if file is full
        else if(strcmp(command, "srmdir") == 0){
            printf("Enter the folder path to remove: ");
            scanf("%255s", path1);
            remove_directory(path1);
        }
        // even if the file is full, remove a folder 
        else if(strcmp(command, "srmdirforce") == 0){
            printf("Enter the folder path to remove with content: ");
            scanf("%255s", path1);
            remove_directory_with_content(path1);
        }
        // makes permission changes
        else if(strcmp(command, "schmod") == 0){
            mode_t permissions;
            printf("Enter the file or folder path to change permissions: ");
            scanf("%255s", path1);

            printf("Enter the new permissions (octal, e.g., 0755): ");
            scanf("%o", &permissions);

            change_permissions(path1, permissions);
        }
        // print the command menu
        else if(strcmp(command, "shelp") == 0){
            print_help();
        }
        // exits the program
        else if(strcmp(command, "sexit") == 0){
            go_exit();
        }
        else{
            printf("Unknown command...");
        }
        

        printf("\nEnter a command: ");
    }

    return 0;
}