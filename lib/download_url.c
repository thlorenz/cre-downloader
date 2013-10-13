#include <curl/curl.h>
#include "download_url.h"

long download_url(char* url, FILE* fp, size_t(*write_data)(void *ptr, size_t size, size_t nmemb, FILE *stream)) {
  CURL *session;
  CURLcode curl_code;
  long http_code;

  session = curl_easy_init();
  if (session) {
    curl_easy_setopt(session, CURLOPT_URL, url);
    curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(session, CURLOPT_WRITEDATA, fp);
    curl_code = curl_easy_perform(session);
    curl_easy_getinfo(session, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(session);

    return curl_code != CURLE_ABORTED_BY_CALLBACK
        && http_code == 200
        ? 0
        : http_code;
  } else {
    return -1;
  }
}

