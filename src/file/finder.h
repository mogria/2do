#ifndef _FINDER_H
#define _FINDER_H
#include <mcstring/mcstring.h>
#include "filebuffer.h"

mcstring *find_line_by_number(filebuffer *buffer, size_t linenumber);
mcstring *find_line_by_word(filebuffer *buffer, const char *word);
mcstring *find_line_by_words(filebuffer *buffer, size_t num_words, const char **words);

#endif /* _FINDER_H */
