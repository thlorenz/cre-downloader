#include <curl/curl.h>
#include "download_url.h"

long download_url (
    const char* url
  , const void* ptr
  , const download_url_wd write_data
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
        ? http_code
        : -1;
  } else {
    return -1;
  }
}
