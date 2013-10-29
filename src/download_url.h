#include <stdio.h>
#ifndef DOWNLOAD_URL_H
#define DOWNLOAD_URL_H

long download_url(
  const char* url,
  const void* ptr,
  const size_t(*write_data)(void *ptr, size_t size, size_t nmemb, void *stream)
);

#endif
