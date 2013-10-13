#include <stdio.h>
#include <stdlib.h>
#include "download_url_buffer.h"

#define ARCHIVE_URL "http://cre.fm/archiv"

int
get_links(char* links[]) {
  DownloadResult res;

  res = download_url_buffer(ARCHIVE_URL);
  if(res.status) return res.status;

  printf("html: %s\n", res.html);

  if(res.html) free(res.html);
  return 0;
}
