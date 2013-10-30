#include <stdio.h>
#ifndef DOWNLOAD_URL_H
#define DOWNLOAD_URL_H

typedef size_t(*download_url_wd)(void *ptr, size_t size, size_t nmemb, void *stream);

long download_url(
  const char*,
  const void*,
  const download_url_wd
);

#endif
