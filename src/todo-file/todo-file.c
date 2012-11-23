#include "todo-file.h"
#include "../exception.h"
#include "../array.h"
#include "../file/file.h"
#include "../file/filebuffer.h"
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
  filebuffer file;
  int i;

  read_file(&file, todo_file);

  truncate_file(todo_file);

  for(i = 0; i < file.num_lines; i++) {
    if(i + 1 != number) {
      char *line = c_string(file.lines[i]);
      fprintf(todo_file, "%s\n", line);
      free(line);
    }
  }

  free_filebuffer(&file);
}
