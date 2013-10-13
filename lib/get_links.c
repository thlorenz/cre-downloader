#include "./open_memstream.h"
#include "./download_url_file.h"

#define ARCHIVE_URL "http://cre.fm/archiv"

int get_links(char* links[]) {
  char* buffer = NULL;
  size_t buffer_size = 0;

  FILE *write_stream = open_memstream(&buffer, &buffer_size);
  download_url_file(ARCHIVE_URL, write_stream);
  fclose(write_stream);

  printf("html: %s\n", buffer);

  return 0;
}
