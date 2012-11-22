#include "list.h"
#include "../array.h"
#include "../todo-file/todo-file.h"
#include "../file/filebuffer.h"
#include "../config/config.h"
#include <mcstring/mcstring.h>
#include <string.h>

int list_command(int argc, char **argv) {
  filebuffer file;
  char *line;
  char *current_line;
  size_t i, maxsize;
  FILE *todo_file = open_todo_file("r");

  read_file(&file, todo_file);

  for(i = 0; i < file.num_lines; i++) {
    int linesize = string_size(file.lines[i]);
    if(maxsize < linesize) {
      maxsize = linesize;
    }
  }
  maxsize += 6;
 
  ALLOC1(char, line, maxsize + 1);
  memset(line, '-', maxsize);

  if(get_config()->list_markdown_table) {
    line[3] = ':';
    line[4] = '|';
    line[5] = ':';
  } else {
    line[4] = '+';
  }
  
  printf("%3s | %s\n", "#", "task");
  printf("%s\n", line);
  FREE1(line);

  for(i = 0; i < file.num_lines; i++) {
    current_line = c_string(file.lines[i]);
    printf("%3u | %s\n", (unsigned int)i, line);
    free(current_line);
  }

  free_filebuffer(&file);
  return 0;
}
