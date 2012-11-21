#include "todo-file.h"
#include "../exception.h"
#include "../array.h"
#include "../file/file.h"
#include "../config/config.h"
#include <stdio.h>

FILE *open_todo_file(const char *mode) {
  FILE *todo_file;
  char *filename = get_config()->todo_filename;
  todo_file = fopen(filename, mode);
  if(todo_file == NULL) {
    THROW("could not open todo file", 1);
  }
  return todo_file;
}

void remove_line_by_number(FILE *todo_file, int number) {
  char **linebuffer;
  size_t *linesizes;
  size_t size;
  size_t i;

  read_file(&linebuffer, &linesizes, &size, todo_file);

  truncate_file(todo_file);

  for(i = 0; i < size; i++) {
    if(i + 1 != number) {
      fprintf(todo_file, "%s\n", linebuffer[i]);
    }
  }

  FREE2(linebuffer, size);
  FREE1(linesizes);
}