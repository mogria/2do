#ifndef _FILEBUFFER_H
#define _FILEBUFFER_H

#include <mcstring/mcstring.h>

typedef struct filebuffer {
  mcstring **lines;
  size_t num_lines;
} filebuffer;

void write_file(filebuffer *buffer, FILE *file);
void read_file(filebuffer *buffer, FILE *file);
void filebuffer_init(filebuffer *buffer);
void filebuffer_append(filebuffer *buffer, mcstring *line);
void free_filebuffer(filebuffer *buffer);
void filebuffer_clear(filebuffer *buffer);
unsigned char filebuffer_remove(filebuffer *buffer, int line_number);
void only_free_filebuffer(filebuffer *buffer);

#endif /* _FILEBUFFER_H */
