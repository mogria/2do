#ifndef _2DO_H
#define _2DO_H

#include "help.h"
#include "add.h"

#define NUM_COMMANDS 3

#define COMMAND_NAMES \
  "help", \
  "add", \
  "remove"

#define COMMAND_FUNCTIONS \
  help_command, \
  add_command, \
  remove_command

#define NO_COMMAND (0)

int void_command(int argc, char **argv);

void gen2d_string_array(char ***array, size_t size, ...);

#endif /* _2DO_H */
