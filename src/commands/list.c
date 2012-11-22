#include "list.h"
#include "../array.h"
#include "../todo-file/todo-file.h"
#include "../file/filebuffer.h"
#include "../config/config.h"
#include <mcstring/mcstring.h>
#include <string.h>

int list_command(int argc, char **argv) {
  filebuffer file;
  char *line;

  //  # | task
  //----+-------------------------
  //  1 | first thing on list
  //  2 | second thing on list and
  //    |  some extra stuff
  //<-------------1-------------->
  //<-2-->
  //      <------------------3-------------------->
  //      <---------4------------>
  // (1) specified_width := <width of the whole output>
  //                        in this case 30
  // (2) required_width := <width required for number column
  //                       and spaces> always 6
  // (3) max_text_size := <max length of a line in buffer>
  //                      in this case 41
  //
  // (4) specified_text_width := <length the text needs to
  //                             be to fit <specified_width>
  //                             in this case 24
  size_t i, max_text_size, max_width, required_space = 6;
  size_t specified_width = get_config()->max_linesize;
  size_t specified_text_width, line_offset;
  size_t current_linesize;
  FILE *todo_file = open_todo_file("r");

  read_file(&file, todo_file);

  for(i = 0; i < file.num_lines; i++) {
    current_linesize = string_size(file.lines[i]);
    if(max_text_size < current_linesize) {
      max_text_size = current_linesize;
    }
  }

  if(specified_width > max_text_size + required_space) {
    max_width = max_text_size + required_space;
  } else {
    max_width = specified_width;
  }

  specified_text_width = max_width - required_space;
 
  ALLOC1(char, line, max_width + 1);
  memset(line, '-', max_width);

  if(get_config()->list_markdown_table) {
    line[3] = ':';
    line[4] = '|';
    line[5] = ':';
  } else {
    line[4] = '+';
  }
  
  printf("%3s | %s\n", "#", "task");
  printf("%s\n", line);
  FREE1(line);

  for(i = 0; i < file.num_lines; i++) {
    line_offset = 0;
    do {
      mcstring *substr = sub_string(file.lines[i], line_offset, specified_text_width);
      line = c_string(substr);
      free_string(substr);
      if(line_offset > 0) {
        printf("    | %s\n", line);
      } else {
        printf("%3u | %s\n", (unsigned int)i, line);
      }
      free(line);
      line_offset += specified_text_width;
    } while(line_offset + specified_text_width <= string_size(file.lines[i]));
  }

  free_filebuffer(&file);
  return 0;
}
