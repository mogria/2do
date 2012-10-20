#ifndef _TODO_FILE_H
#define _TODO_FILE_H
#include <stdio.h>

FILE *open_todo_file(const char *mode);
void remove_line_by_number(FILE *todo_file, int number);
void read_todo_file(char ***buffer, size_t **linesizes, size_t *size, FILE *todo_file);
void truncate_todo_file(FILE *todo_file);

#endif /* _TODO_FILE_H */
