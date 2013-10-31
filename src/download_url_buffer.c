#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./download_url.h"
#include "./download_url_buffer.h"

typedef struct MemoryStruct {
  char *memory;
  size_t size;
} MemoryStruct;

static size_t write_chunk_to_memory(void *contents, size_t size, size_t nmemb, void *userp) {
  size_t realsize = size * nmemb;
  MemoryStruct *mem = (MemoryStruct *)userp;

  mem->memory = realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }

  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;

  return realsize;
}

DownloadResult download_url_buffer(const char* url) {
  MemoryStruct chunk;
  chunk.memory = malloc(1);
  chunk.size = 0;

  long status = download_url(url, (void *) &chunk, write_chunk_to_memory);

  DownloadResult res;
  res.html = chunk.memory;
  res.size = chunk.size;
  res.status = status;

  return res;
}
