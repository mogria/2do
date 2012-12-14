#ifndef _TODO_FILE_H
#define _TODO_FILE_H
#include <stdio.h>

FILE *open_todo_file(const char *mode);
unsigned char remove_line_by_number(FILE *todo_file, int number);

#endif /* _TODO_FILE_H */
