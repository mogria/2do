#ifndef _CONFIG_H
#define _CONFIG_H

#include <stddef.h>

struct config;
#include "default-config.h"

#define CONFIG_DIRECTIVE_SIZE ((size_t)32)
#define CONFIG_VALUE_SIZE ((size_t)255)
#define CONFIG_LINE_FORMAT_SIZE (30)
#define CONFIG_NUM_DIRECTIVES 3

struct config {
  short list_markdown_table;
  char todo_filename[CONFIG_VALUE_SIZE];
  char max_linesize;
};

struct config *get_config();
void get_config_value(struct config *config, char *directive, char *dest, size_t dest_size);
void parse_config_file(struct config *config, char *filename);
int config_command(int argc, char **argv);

#endif /* _CONFIG_H */
