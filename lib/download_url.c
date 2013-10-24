#include <curl/curl.h>
#include "download_url.h"

long download_url (
    const char* url
  , const void* ptr
  , const size_t(*write_data)(void *ptr, size_t size, size_t nmemb, void *stream)
  ) {

  CURL *curl_handle;
  CURLcode curl_code;
  const long http_code;

  curl_handle = curl_easy_init();
  if (curl_handle) {
    curl_easy_setopt(curl_handle, CURLOPT_URL, url);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, ptr);
    curl_code = curl_easy_perform(curl_handle);
    curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

    curl_easy_cleanup(curl_handle);

    return curl_code != CURLE_ABORTED_BY_CALLBACK
        && http_code == 200
        ? 0
        : http_code;
  } else {
    return -1;
  }
}
