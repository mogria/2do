#ifndef _FINDER_H
#define _FINDER_H

char *find_line_by_number(char **buffer, size_t size, size_t *linesizes, int linenumber);
char *find_line_by_words(char **words);

#endif /* _FINDER_H */
