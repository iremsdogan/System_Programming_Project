#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void copy_file(const char *src, const char *dest);
void remove_file(const char *path);
void read_file(const char *path);
void write_file(const char *path);
void move_file(const char *src, const char *dest);
void create_file(const char *path);
void rename_file(const char *old_name, const char *new_name);
void search_files(const char *dir_path, const char *search_term);
void display_file(const char *path); 

#endif // FILE_OPERATIONS_H
