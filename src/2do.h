#ifndef _2DO_H
#define _2DO_H

#define NUM_COMMANDS 5

#define COMMAND_NAMES \
  "help", \
  "add", \
  "remove", \
  "list", \
  "config"

#define COMMAND_FUNCTIONS \
  help_command, \
  add_command, \
  remove_command, \
  list_command, \
  config_command

#define NO_COMMAND (0)

int void_command(int argc, char **argv);

void gen2d_string_array(char ***array, size_t size, ...);

#endif /* _2DO_H */
