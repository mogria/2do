#include "list.h"
#include "array.h"
#include "todo-file.h"
#include <string.h>

int list_command(int argc, char **argv) {
  char **buffer;
  char *line;
  size_t *linesizes;
  size_t size;
  size_t i;
  size_t maxsize = 4;
  FILE *todo_file = open_todo_file("r");

  read_todo_file(&buffer, &linesizes, &size, todo_file);

  for(i = 0; i < size; i++) {
    if(maxsize < linesizes[i]) {
      maxsize = linesizes[i];
    }
  }
  maxsize += 6;
 
  ALLOC1(char, line, maxsize + 1);
  memset(line, '-', maxsize);
  line[4] = '+';
  
  printf("%3s | %s\n", "#", "task");
  printf("%s\n", line);
  for(i = 0; i < size; i++) {
    printf("%3i | %s\n", i + 1, buffer[i]);
  }

  FREE1(line);
  FREE1(linesizes);
  FREE2(buffer, size);

  return 0;
}
