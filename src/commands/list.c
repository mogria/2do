#include "list.h"
#include "../array.h"
#include "../todo-file/todo-file.h"
#include "../file/file.h"
#include "../config/config.h"
#include <string.h>

int list_command(int argc, char **argv) {
  char **buffer;
  char *line;
  size_t *linesizes;
  size_t size;
  size_t i, u;
  size_t maxsize = 4;
  int max_linesize = get_config()->max_linesize;
  int linepos = 0;
  int current_linesize = 0;
  unsigned char printed_number = 0;
  FILE *todo_file = open_todo_file("r");

  read_file(&buffer, &linesizes, &size, todo_file);

  for(i = 0; i < size; i++) {
    if(maxsize < linesizes[i]) {
      maxsize = linesizes[i];
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
  for(i = 0; i < size; i++) {
    printed_number = 0;
    linepos = 0;
    current_linesize = max_linesize <= 10 ? linesizes[i] : max_linesize - 6;
    do {
      if(!printed_number) {
        printf("%3lu | ", i + 1);
        printed_number = 1;
      } else {
        printf("    | ");
      }
      for(u = 0; u < current_linesize && u + linepos < linesizes[i]; u++) {
        printf("%c", buffer[i][linepos + u]);
      }
      puts("");
      linepos += current_linesize;
    } while(linepos < linesizes[i]);
    
  }

  FREE1(line);
  FREE1(linesizes);
  FREE2(buffer, size);

  return 0;
}
