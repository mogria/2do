#include "filebuffer.h"
#include "../array.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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
  size_t linesize = 1;

  // go back to the start of the file
  rewind(file);

  filebuffer_init(buffer);
  ALLOC1(char, line, 1);

  // iterate through the file until the end
  while((c = fgetc(file)) != EOF) {

    // create a new element to the buffer if a new line begins
    if(c == '\n') {
      line[linesize - 1] = '\0';
      filebuffer_append(buffer, new_string(line));
      linesize = 1;
      RALLOC1(char, line, linesize);
    } else {
      linesize++;
      RALLOC1(char, line, linesize);
      line[linesize - 2] = c;
    }
  }

  FREE1(line);
}

void filebuffer_init(filebuffer *buffer) {
  buffer->num_lines = 0;
  ALLOC1(mcstring *, buffer->lines, buffer->num_lines);
}

void filebuffer_append(filebuffer *buffer, mcstring *line) {
  RALLOC1(mcstring *, buffer->lines, ++buffer->num_lines);
  buffer->lines[buffer->num_lines - 1] = line;
}

void filebuffer_clear(filebuffer *buffer) {
  free_filebuffer(buffer);
  filebuffer_init(buffer);
}

unsigned char filebuffer_remove(filebuffer *buffer, int line_number) {
  // linenumber == 0 -> clear()
  // linenumber > 0 -> remove line with this number
  // linenumber < 0 -> same as above, but relative
  //                   to the end of the file

  unsigned char ret = 1;
  if(line_number == 0) {
    filebuffer_clear(buffer);
  } else {
    if(line_number < 0) {
      line_number = buffer->num_lines - line_number + 1;
    }
    line_number--;
    
    if((ret = (line_number >= 0 && line_number < buffer->num_lines))) {
      memmove(&buffer->lines[line_number],
        &buffer->lines[line_number + 1],
        sizeof(mcstring*) * (buffer->num_lines - 1 - line_number));
      RALLOC1(mcstring *, buffer->lines, ++buffer->num_lines);
    }
  }

  return ret;
}

void free_filebuffer(filebuffer *buffer) {
  int x;
  for(x = 0; x < buffer->num_lines; x++) {
    free_string(buffer->lines[x]);
  }
  only_free_filebuffer(buffer);
}

void only_free_filebuffer(filebuffer *buffer) {
  FREE1(buffer->lines);
  buffer->num_lines = 0;
}
