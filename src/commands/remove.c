#include "remove.h"
#include "../arguments.h"
#include "../exception.h"
#include "../todo-file/todo-file.h"
#include <stdlib.h>

int remove_command(int argc, char **argv) {
  int id;
  FILE *todo_file;

  clear_empty_arguments(&argc, &argv);

  if(!argc) {
    THROW("no id given", 3);
  }

  id = atoi(argv[0]);

  if(!id) {
    THROW("invalid id given", 4);
  }

  todo_file = open_todo_file("r+");

  remove_line_by_number(todo_file, id);

  fclose(todo_file);
  return 0;
}
