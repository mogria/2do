#include "todo-file.h"
#include "default-config.h"
#include "exception.h"
#include <stdio.h>

FILE *open_todo_file(const char *mode) {
  FILE *todo_file;
  todo_file = fopen(DEFAULT_FILENAME, mode);
  if(todo_file == NULL) {
    THROW("could not open todo file", 1);
  }
  return todo_file;
}
