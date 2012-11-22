#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "exception.h"
#include "2do.h"
#include "commands/help.h"
#include "commands/version.h"
#include "commands/add.h"
#include "commands/remove.h"
#include "commands/list.h"
#include "commands/done.h"
#include "commands/config.h"


int main(int argc, char **argv) {
  char **command_names;
  int (*commands[])(int, char**) = {COMMAND_FUNCTIONS};
  int (*command)(int, char**) = void_command;
  int i, back;

  gen2d_string_array(&command_names, NUM_COMMANDS, COMMAND_NAMES);

  if(argc > 1) {
    for(i = 0; i < NUM_COMMANDS; i++) {
      if(strcmp(argv[1], command_names[i]) == 0) {
        command = commands[i];
      }
    }
    
    if(command == void_command) {
      command = help_command;
      fprintf(stderr, "Unknown command: '%s'\n", argv[1]);
    }
  } else {
    command = help_command;
  }

  free(command_names);

  TRY {
    back = command(argc - 2, argv + 2);
  } CATCH {
    fprintf(stderr, "error #%i %s\n", EXCEPTION_ERRCODE, EXCEPTION_MESSAGE);
    back = 1;
  }
  return back;
}


int void_command(int argc, char **argv) {
  return 0;
}

void gen2d_string_array(char ***array, size_t size, ...) {
  va_list list;
  int i;
  *array = malloc(size * sizeof(char*));

  va_start(list, size);
  for(i = 0; i < size; i++) {
    (*array)[i] = va_arg(list, char*);
  }
  va_end(list);
}
