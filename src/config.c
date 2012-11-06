#include "config.h"
#include "exception.h"
#include "array.h"
#include "file.h"
#include "info.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

#define DIRECTIVE_SIZE ((size_t)32)
#define VALUE_SIZE ((size_t)255)
#define LINE_FORMAT_SIZE (30)
#define NUM_DIRECTIVES 1

static struct config _offset = {};

void set_config_value_int(struct config *config, void *dest, char *value) {
  *(int*)dest = atoi(value);
}

void set_config_value_bool(struct config *config, void *dest, char *value) {
  if((value[0] | 0x20) == 't') {
    *(short*)dest = 1;
  } else if((value[0] | 0x20) == 'f') {
    *(short*)dest = 0;
  } else {
    *(short*)dest = atoi(value) == 0 ? 0 : 1;
  }
}

void set_config_value_string(struct config *config, void *dest, char *value) {
  size_t len = strlen(value);
  strncpy((char*)dest, value, VALUE_SIZE < len ? VALUE_SIZE : len);
}

void get_config_value_int(struct config *config, void *source, char *dest, size_t dest_size) {
  snprintf(dest, dest_size, "%i", *(int *)source);
}

void get_config_value_bool(struct config *config, void *source, char *dest, size_t dest_size) {
  strncpy(dest, *(short *)source ? "true" : "false", dest_size);
}

void get_config_value_string(struct config *config, void *source, char *dest, size_t dest_size) {
  strncpy(dest, (char *)source, dest_size);
}

static char config_directives[NUM_DIRECTIVES][DIRECTIVE_SIZE] = {
  "list_markdown_table"
};

static ptrdiff_t config_offsets[NUM_DIRECTIVES] = {
   (char *)&_offset.list_markdown_table - (char *)&_offset
};

static size_t config_function_mapping[NUM_DIRECTIVES] = {
  1
};

static void (*config_setter_functions[])(struct config*, void*, char*) = {
  set_config_value_int,
  set_config_value_bool,
  set_config_value_string
};

static void (*config_getter_functions[])(struct config*, void*, char*, size_t) = {
  get_config_value_int,
  get_config_value_bool,
  get_config_value_string
};


void initialize_config(struct config *config) {
  config->list_markdown_table = 0;
}

char *get_fscanf_format_config_line() {
  static char fscanf_format[LINE_FORMAT_SIZE] = {};

  if(*fscanf_format == '\0') {
    snprintf(fscanf_format, LINE_FORMAT_SIZE, "%%%i[^ ]%%*[ ]%%%i[^\r\n]", DIRECTIVE_SIZE, VALUE_SIZE);
  }
  return fscanf_format;
}

int get_config_directive_index(struct config *config, char *directive) {
  int i, match = -1;

  for(i = 0; i < NUM_DIRECTIVES; i++) {
    if(strcmp(directive, config_directives[i]) == 0) {
      match = i;
      break;
    }
  }
  return match;
}

void get_config_value(struct config *config, char *directive, char *dest, size_t dest_size) {
  int match = get_config_directive_index(config, directive);   
  if(match >= 0) {
    config_getter_functions[config_function_mapping[match]](
      config,
      (void *)((char*)config + config_offsets[match]),
      dest,
      dest_size
    );
  }
}

void set_config_value(struct config *config, char *directive, char *value) {
  int match = get_config_directive_index(config, directive);   
  if(match >= 0) {
    config_setter_functions[config_function_mapping[match]](
      config,
      (void *)((char *)config + config_offsets[match]),
      value
    );
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
    num_results = sscanf(buffer[i], fscanf_format, current_directive, current_value);
    if(num_results == 2) { // found two strings (directive and value) on the current line?
      set_config_value(config, current_directive, current_value);
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
    FILE *file;
    if((file = fopen(CONFIG_FILE, "r")) != NULL) {
      fclose(file);
      parse_config_file(&config, CONFIG_FILE);
    }
    initialized = 1;
  }
  return &config;
}


int config_command(int argc, char **argv) {
  char dest[255];
  if(argv[0] > 0) {
    get_config_value(get_config(), argv[0], dest, 255); 
    printf("%s %s\n", argv[0], dest);
  } else {
    puts("Usage: 2do config <directive> [new_value]");
  }
  return 0;
}
