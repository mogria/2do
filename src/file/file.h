#ifndef _FILE_H
#define _FILE_H

#include <stdio.h>

void read_file(char ***buffer, size_t **linesizes, size_t *size, FILE *file);
void truncate_file(FILE *file);

#endif /* _FILE_H */
