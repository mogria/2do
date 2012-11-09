#include "file.h"
#include "../array.h"
#include "../exception.h"
#include <stdlib.h>
#include <stdio.h>

void read_file(char ***buffer, size_t **linesizes, size_t *size, FILE *file) {
  char c;
  size_t current_linesize = 0;
  *size = 1;

  // go back to start of the file
  rewind(file);

  // allocate memory for char pointers & size_t's
  // to store the line length of each line
  ALLOC1(char *, *buffer, *size);
  ALLOC1(size_t, *linesizes, *size);
  (*linesizes)[*size - 1] = 0;
  ALLOC1(char, (*buffer)[*size - 1], (*linesizes)[*size - 1]);

  // iterate through the file until the end
  while((c = fgetc(file)) != EOF) {

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

  if((*linesizes)[*size - 1] == 0) {
    (*size)--;
    RALLOC1(size_t, *linesizes, *size);
    FREE1((*buffer)[*size]);
  }
}


void truncate_file(FILE *file) {
  FILE *reopen;
  rewind(file);
  reopen = freopen(NULL, "w", file);
  if(reopen == NULL) {
    THROW("could not truncate file", 5);
  }
}
