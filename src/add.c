#include "add.h"
#include "exception.h"
#include "todo-file.h"

int add_command(int argc, char **argv) {
  FILE *todo_file = open_todo_file("a");
  int i, copy_by = 0;
  char append = ' ';

  // remove empty paramters
  for(i = 0; i < argc; i++) {
    argv[i - copy_by] = argv[i];
    if(strcmp(argv[i], "") == 0) {
      copy_by++;
    } 
  }
  argc -= copy_by;

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
