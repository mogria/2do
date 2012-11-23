#include "list.h"
#include "../array.h"
#include "../todo-file/todo-file.h"
#include "../file/filebuffer.h"
#include "../config/config.h"
#include <string.h>

int list_command(int argc, char **argv) {
  filebuffer file;
  char *line;
  size_t i, u;
  size_t maxsize = 4;
  int max_linesize = get_config()->max_linesize;
  int linepos = 0;
  int current_linesize = 0;
  unsigned char printed_number = 0;
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
  memset(line, '-', max_linesize <= 10 ? maxsize : max_linesize);

  if(get_config()->list_markdown_table) {
    line[3] = ':';
    line[4] = '|';
    line[5] = ':';
  } else {
    line[4] = '+';
  }
  
  printf("%3s | %s\n", "#", "task");
  printf("%s\n", line);
  for(i = 0; i < file.num_lines; i++) {
    printed_number = 0;
    linepos = 0;
    current_linesize = max_linesize <= 10 ? string_size(file.lines[i]) : max_linesize - 6;
    copy_string(line, file.lines[i], current_linesize);
    do {
      if(!printed_number) {
        printf("%3u | ", (unsigned int)i + 1);
        printed_number = 1;
      } else {
        printf("    | ");
      }
      for(u = 0; u < current_linesize && u + linepos < string_size(file.lines[i]); u++) {
        printf("%c", line[linepos + u]);
      }
      puts("");
      linepos += current_linesize;
    } while(linepos < string_size(file.lines[i]));
    free(line);
  }

  free_filebuffer(&file);
  return 0;
}
