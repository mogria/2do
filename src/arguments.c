#include "arguments.h"
#include <string.h>

void clear_empty_arguments(int *argc, char ***argv) {
  int i, copy_by = 0;
  for(i = 0; i < *argc; i++) {
    (*argv)[i - copy_by] = (*argv)[i];
    if(strcmp((*argv)[i], "") == 0) {
      copy_by++;
    } 
  }
  *argc -= copy_by;
}
