#include "filebuffer.h"
#include "../array.h"
#include <stddef.h>
#include <stdio.h>

void write_file(filebuffer *buffer, FILE *file) {
  int x;
  char *line;
  for(x = 0; x < buffer->num_lines; x++) {
    line = c_string(buffer->lines[x]);
    fprintf(file, "%s\n", line);
    free(line);
  }
}

void read_file(filebuffer *buffer, FILE *file) {
  char c;
  char *line;
  buffer->num_lines = 0;
  size_t linesize = 1;

  // go back to the start of the file
  rewind(file);

  ALLOC1(mcstring *, buffer->lines, buffer->num_lines);
  ALLOC1(char, line, 1);

  // iterate through the file until the end
  while((c = fgetc(file)) != EOF) {

    // create a new element to the buffer if a new line begins
    if(c == '\n') {
      line[linesize] = '\0';
      linesize = 1;
      RALLOC1(mcstring *, buffer->lines, ++buffer->num_lines);
      buffer->lines[buffer->num_lines - 1] = new_string(line);
      RALLOC1(char, line, linesize);
    } else {
      linesize++;
      RALLOC1(char, line, linesize);
      line[linesize - 2] = c;
    }
  }

  FREE1(line);
}

void free_filebuffer(struct filebuffer *buffer) {
  buffer->num_lines = 0;
  FREE1(buffer->lines);
}


