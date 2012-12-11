#include "finder.h"

mcstring *find_line_by_number(filebuffer *buffer, size_t linenumber) {
  if(linenumber > 0 && linenumber <= buffer->num_lines) {
    return buffer->lines[linenumber];
  }
  return NULL;
}

mcstring *find_line_by_word(filebuffer *buffer, const char *word) {
  return find_line_by_words(buffer, 1, &word);
}

mcstring *find_line_by_words(filebuffer *buffer, size_t num_words, const char **words) {
  static filebuffer *static_buffer = NULL;
  static const char **static_words = NULL;
  static size_t static_num_words = 0;
  static size_t static_line = 0;

  if(words == NULL) {
    words = static_words;
    num_words = static_num_words;
  }

  if(buffer == NULL) {
    buffer = static_buffer;
  } else {
    static_line = 0;
  }

  mcstring *back = NULL;

  size_t line;
  size_t i;

  for(line = static_line; line < buffer->num_lines; line++) {
    for(i = 0; i < num_words ; i++) {
      search_cstring(buffer->lines[line], words[i]);
    }
  }

  static_buffer = buffer;
  static_words = words;
  static_num_words = num_words;
  static_line = line;

  return back;
}
