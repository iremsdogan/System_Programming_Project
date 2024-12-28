#ifndef DIRECTORY_OPS_H
#define DIRECTORY_OPS_H

void list_directory(const char *path);
void create_directory(const char *path);
void remove_directory(const char *path);
void remove_directory_with_content(const char *path);

#endif // DIRECTORY_OPS_H
