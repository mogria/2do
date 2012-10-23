#ifndef _CONFIG_H
#define _CONFIG_H

struct config {
  short list_markdown_table;
};


struct config *get_config();
void parse_config_file(struct config *config, char *filename);

#endif /* _CONFIG_H */
