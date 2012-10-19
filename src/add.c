#include "add.h"
#include "todo-file.h"

int add_command(int argc, char **argv) {
  FILE *todo_file = open_todo_file("a");
  int i;
  char append = ' ';

  for(i = 0; i < argc; i++) {
    if(i + 1 == argc) {
      append = '\n';
    }
    fprintf(todo_file, "%s%c", argv[i], append);
  }

  fclose(todo_file);

  return 0;
}
