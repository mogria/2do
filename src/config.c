#include "config.h"
#include "exception.h"
#include "array.h"
#include "file.h"
#include <stdio.h>
#include <stdlib.h>

#define DIRECTIVE_SIZE ((size_t)32)
#define VALUE_SIZE ((size_t)255)
#define LINE_FORMAT_SIZE (30)
#define NUM_DIRECTIVES 1

void set_list_markdown_table(struct config *config, char *value) {
  config->list_markdown_table = (short)(atoi(value) != 0 ? 1 : 0);
}

static char config_directives[NUM_DIRECTIVES][DIRECTIVE_SIZE] = {
  "list_markdown_table"
};

static void (*config_update_function[NUM_DIRECTIVES])(struct config*, char *) = {
  set_list_markdown_table
};


void initialize_config(struct config *config) {
  config->list_markdown_table = 0;
}

char *get_fscanf_format_config_line() {
  static char fscanf_format[LINE_FORMAT_SIZE] = {};

  if(*fscanf_format == '\0') {
    snprintf(fscanf_format, LINE_FORMAT_SIZE, "%%%is=%%%is", DIRECTIVE_SIZE, VALUE_SIZE);
  }

  return fscanf_format;
}

void process_config_directive(struct config *config, char *directive, char *value) {
  int i, match = -1;

  for(i = 0; i < NUM_DIRECTIVES; i++) {
    if(strcmp(directive, config_directives[i]) == 0) {
      match = i;
      break;
    }
  }
      
  if(match >= 0) {
    config_update_function[match](config, value);
  }
}

void parse_config_file(struct config *config, char *filename) {
  char **buffer;
  size_t *linesizes;
  size_t size;
  int i;
  int num_results;
  char current_directive[DIRECTIVE_SIZE];
  char current_value[VALUE_SIZE];
  char *fscanf_format = get_fscanf_format_config_line();
  FILE *file = fopen(filename, "r");

  if(file == NULL) {
    THROW("could not open config file", 6);
  }

  read_file(&buffer, &linesizes, &size, file);
  fclose(file);

  for(i = 0; i < size; i++) {
    memset(current_directive, 0, DIRECTIVE_SIZE);
    memset(current_value, 0, VALUE_SIZE);
    num_results = sscanf(buffer[i], fscanf_format, &current_directive, &current_value);
    if(num_results == 2) { // found two strings (directive and value) on the current line?
      process_config_directive(config, current_directive, current_value);
    }
  }

  FREE2(buffer, size);
  FREE1(linesizes);
}

struct config *get_config() {
  static struct config config = {};
  static short initialized = 0;
  if(!initialized) {
    initialize_config(&config);
    initialized = 1;
  }
  return &config;
}


void cofig_command(int argc, char **argv) {
}
