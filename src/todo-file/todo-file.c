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

unsigned char remove_line_by_number(FILE *todo_file, int number) {
  filebuffer file;
  unsigned char ret;

  read_file(&file, todo_file);

  if((ret = filebuffer_remove(&file, number))) {
    truncate_file(todo_file);
    write_file(&file, todo_file);
  }

  free_filebuffer(&file);

  return ret;
}
