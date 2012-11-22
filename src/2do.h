#ifndef _2DO_H
#define _2DO_H

#define NUM_COMMANDS 7

#define COMMAND_NAMES \
  "help", \
  "version", \
  "add", \
  "remove", \
  "list", \
  "config", \
  "done"

#define COMMAND_FUNCTIONS \
  help_command, \
  version_command, \
  add_command, \
  remove_command, \
  list_command, \
  config_command, \
  done_command

#define NO_COMMAND (0)

int void_command(int argc, char **argv);

void gen2d_string_array(char ***array, size_t size, ...);

#endif /* _2DO_H */
