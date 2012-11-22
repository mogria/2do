#include "version.h"
#include "../info.h"
#include <stdio.h>

int version_command(int argc, char **argv) {
  puts(VERSION);
  return 0;
}
