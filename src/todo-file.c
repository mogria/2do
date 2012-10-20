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


void read_todo_file(char ***buffer, size_t **linesizes, size_t *size, FILE *todo_file) {
  char c;
  size_t current_linesize = 0;
  *size = 1;

  // go back to start of the file
  rewind(todo_file);

  // allocate memory for char pointers & size_t's
  // to store the line length of each line
  ALLOC1(char *, *buffer, *size);
  ALLOC1(size_t, *linesizes, *size);
  (*linesizes)[*size - 1] = 0;
  ALLOC1(char, (*buffer)[*size - 1], (*linesizes)[*size - 1]);

  // iterate through the file until the end
  while((c = fgetc(todo_file)) != EOF) {

    // create a new element to the buffer if a new line begins
    if(c == '\n') {
      (*size)++;
      RALLOC1(char *, *buffer, *size);
      RALLOC1(size_t, *linesizes, *size);
      (*linesizes)[(int)(*size - 1)] = 0;
      ALLOC1(char, (*buffer)[*size - 1], (*linesizes)[*size - 1]);
    } else {
      current_linesize = ++((*linesizes)[*size - 1]);
      RALLOC1(char, (*buffer)[*size - 1], current_linesize);
      (*buffer)[*size - 1][current_linesize - 1] = c;
    }
  }
}

void remove_line_by_number(FILE *todo_file, int number) {
  char **linebuffer;
  size_t *linesizes;
  size_t size;
  size_t i;

  read_todo_file(&linebuffer, &linesizes, &size, todo_file);

  truncate_todo_file(todo_file);

  for(i = 0; i < size - 1; i++) {
    if(i + 1 != number) {
      fprintf(todo_file, "%s\n", linebuffer[i]);
    }
  }

  FREE2(linebuffer, size);
  FREE1(linesizes);
}
