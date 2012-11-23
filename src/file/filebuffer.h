#ifndef _FILEBUFFER_H
#define _FILEBUFFER_H

#include <mcstring/mcstring.h>

typedef struct filebuffer {
  mcstring **lines;
  size_t num_lines;
} filebuffer;

void write_file(struct filebuffer *buffer, FILE *file);
void read_file(struct filebuffer *buffer, FILE *file);
void free_filebuffer(struct filebuffer *buffer);

#endif /* _FILEBUFFER_H */
