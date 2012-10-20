#include "todo-file.h"
#include "default-config.h"
#include "exception.h"
#include "array.h"
#include <stdio.h>

FILE *open_todo_file(const char *mode) {
  FILE *todo_file;
  todo_file = fopen(DEFAULT_FILENAME, mode);
  if(todo_file == NULL) {
    THROW("could not open todo file", 1);
  }
  return todo_file;
}

void truncate_todo_file(FILE *todo_file) {
  FILE *reopen;
  rewind(todo_file);
  reopen = fopen(DEFAULT_FILENAME, "w");
  if(reopen == NULL) {
    THROW("could not truncate todo file", 5);
  }
}

void remove_line_by_number(FILE *todo_file, int number) {
  char **linebuffer;
  int size = 1;
  int *linesizes;
  int current_linesize = 0;
  int i;

  char c = '\n';

  ALLOC1(char *, linebuffer, size);
  ALLOC1(int, linesizes, size);
  linesizes[size - 1] = 0;
  ALLOC1(char, linebuffer[size - 1], linesizes[size - 1]);
  while((c = fgetc(todo_file)) != EOF) {
    if(c == '\n') {
      size++;
      RALLOC1(char *, linebuffer, size);
      RALLOC1(int, linesizes, size);
      linesizes[size - 1] = 0;
      ALLOC1(char, linebuffer[size - 1], linesizes[size - 1]);
    } else {
      current_linesize = ++linesizes[size - 1];
      RALLOC1(char, linebuffer[size - 1], current_linesize);
      linebuffer[size - 1][current_linesize - 1] = c;
    }
  }

  truncate_todo_file(todo_file);

  for(i = 0; i < size - 1; i++) {
    if(i + 1 != number) {
      fprintf(todo_file, "%s\n", linebuffer[i]);
    }
  }

  FREE2(linebuffer, size);
  FREE1(linesizes);
}
