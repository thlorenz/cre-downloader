#include <stdio.h>
#ifndef DOWNLOAD_URL_H
#define DOWNLOAD_URL_H

long download_url(char* url, FILE* fp, size_t(*write_data)(void *ptr, size_t size, size_t nmemb, FILE *stream));

#endif
