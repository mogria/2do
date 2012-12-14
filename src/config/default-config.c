#include "default-config.h"
#include <string.h>

void initialize_config(struct config *config) {
  config->list_markdown_table = 0;
  strncpy(config->todo_filename, DEFAULT_FILENAME, CONFIG_VALUE_SIZE);
  config->max_linesize = 80;
}

