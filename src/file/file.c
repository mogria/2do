#include "file.h"
#include "../array.h"
#include "../exception.h"
#include <stdlib.h>
#include <stdio.h>

void truncate_file(FILE *file) {
  FILE *reopen;
  rewind(file);
  reopen = freopen(NULL, "w", file);
  if(reopen == NULL) {
    THROW("could not truncate file", 5);
  }
}
