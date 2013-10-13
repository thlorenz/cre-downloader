#include <stdio.h>
#include "./download_url.h"

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written = fwrite(ptr, size, nmemb, stream);
  return written;
}

long download_url_file(char* url, FILE* fp) {
  return download_url(url, fp, write_data);
}
