#include <stdio.h>
#ifndef DOWNLOAD_URL_BUFFER_H
#define DOWNLOAD_URL_BUFFER_H

typedef struct DownloadResult {
  char *html;
  size_t size;
  long status;
} DownloadResult;

DownloadResult download_url_buffer(const char* url);

#endif
