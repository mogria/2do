#include <stdio.h>
#include "info.h"
#include "help.h"

int help_command(int argc, char **argv) {
  puts(USAGE);
  return 0;
}
