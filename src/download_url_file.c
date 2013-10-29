#include <stdio.h>
#include "./download_url.h"

const static size_t write_chunk_to_file(void *ptr, size_t size, size_t nmemb, void *stream) {
  return fwrite(ptr, size, nmemb, (FILE *)stream);
}

long download_url_file(const char* url, const FILE* fp) {
  return download_url(url, (void *)fp, write_chunk_to_file);
}
