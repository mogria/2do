#include "add.h"
#include "../exception.h"
#include "../arguments.h"
#include "../todo-file/todo-file.h"

int add_command(int argc, char **argv) {
  FILE *todo_file = open_todo_file("a");
  int i;
  char append = ' ';
  clear_empty_arguments(&argc, &argv);
  
  // if no or only empty arguments are given, throw an exception
  if(!argc) {
    fclose(todo_file);
    THROW("no message given", 2);
  }

  // else write new line info file
  for(i = 0; i < argc; i++) {
    if(i + 1 == argc) {
      append = '\n';
    }
    fprintf(todo_file, "%s%c", argv[i], append);
  }

  fclose(todo_file);

  return 0;
}
