#include "config-command.h"
#include <stdio.h>

int config_command(int argc, char **argv) {
  char dest[255];
  if(argv[0] > 0) {
    get_config_value(get_config(), argv[0], dest, 255); 
    printf("%s '%s'\n", argv[0], dest);
  } else {
    puts("Usage: 2do config <directive> [new_value]");
  }
  return 0;
}
