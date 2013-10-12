#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>

#define ROOT_URL "http://meta.metaebene.me/media/cre/"
#define MAXNAME 10
#define MAXURL sizeof(ROOT_URL) + MAXNAME

void get_url(int n, char* name, char* url) {

  strcpy(url, ROOT_URL);
  strcat(url, name);
}

FILE* get_relative_writestream(char* subdir, char* name) {
  char cwd[PATH_MAX];
  char full_path[PATH_MAX];

  getcwd(cwd, sizeof(cwd));
  strcpy(full_path, cwd);
  strcat(full_path, subdir);
  strcat(full_path, name);
  return fopen(full_path, "wb");
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written = fwrite(ptr, size, nmemb, stream);
  return written;
}

void get_name(int n, char* name) {
  char* padding =
      n < 10  ? "00"
    : n < 100 ? "0"
    : "";

  sprintf(name, "cre%s%d.mp3", padding, n);
}

long download_url(char* url, char* name, FILE* fp) {
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

void download_episode(int n) {
  char name [MAXNAME];
  char url [MAXURL];
  FILE *fp;

  get_name(n, name);
  get_url(n, name, url);
  fp = get_relative_writestream("casts", name);

  printf("Downloading: %s\n", url);

  long status = download_url(url, name, fp);
  if (status) printf("Download failed with status: %ld\n", status);

  fclose(fp);
}

int main(int argc, const char *argv[]) {
  /*int i;
  for (i = 1; i < 10; i++) {
    download_episode(i);
  }*/

  download_episode(3);
  return 0;
}
