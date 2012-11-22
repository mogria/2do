#include "config.h"
#include "../exception.h"
#include "../array.h"
#include "../file/filebuffer.h"
#include "../info.h"
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

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
  memset((char*)dest, 0, CONFIG_VALUE_SIZE);
  int len = strlen(value);
  len = len < CONFIG_VALUE_SIZE - 1 ? len : CONFIG_VALUE_SIZE - 1; 
  strncpy((char*)dest, value, len);
  ((char*)dest)[len] = '\0';
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

static char config_directives[CONFIG_NUM_DIRECTIVES][CONFIG_DIRECTIVE_SIZE] = {
  "list_markdown_table",
  "todo_filename",
  "max_linesize"
};

static ptrdiff_t config_offsets[CONFIG_NUM_DIRECTIVES] = {
   (char *)&_offset.list_markdown_table - (char *)&_offset,
   (char *)&_offset.todo_filename - (char *)&_offset,
   (char *)&_offset.max_linesize - (char *)&_offset
};

static size_t config_function_mapping[CONFIG_NUM_DIRECTIVES] = {
  1,
  2,
  0
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

char *get_fscanf_format_config_line() {
  static char fscanf_format[CONFIG_LINE_FORMAT_SIZE] = {};

  if(*fscanf_format == '\0') {
    snprintf(fscanf_format, CONFIG_LINE_FORMAT_SIZE, "%%%lu[a-z_]%%*[ ]%%%lu[^\x01-\x1F]", CONFIG_DIRECTIVE_SIZE, CONFIG_VALUE_SIZE);
  }
  return fscanf_format;
}

int get_config_directive_index(struct config *config, char *directive) {
  int i, match = -1;

  for(i = 0; i < CONFIG_NUM_DIRECTIVES; i++) {
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
  filebuffer buffer;
  char *line;
  int i;
  int num_results;
  char current_directive[CONFIG_DIRECTIVE_SIZE];
  char current_value[CONFIG_VALUE_SIZE];
  char *fscanf_format = get_fscanf_format_config_line();
  FILE *file = fopen(filename, "r");

  if(file == NULL) {
    THROW("could not open config file", 6);
  }

  read_file(&buffer, file);
  fclose(file);

  for(i = 0; i < buffer.num_lines; i++) {
    memset(current_directive, 0, CONFIG_DIRECTIVE_SIZE);
    memset(current_value, 0, CONFIG_VALUE_SIZE);
    line = c_string(buffer.lines[i]);
    num_results = sscanf(line, fscanf_format, current_directive, current_value);
    free(line);
    if(num_results == 2) { // found two strings (directive and value) on the current line?
      set_config_value(config, current_directive, current_value);
    }
  }

  free_filebuffer(&buffer);
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



