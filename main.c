#include <stdio.h>
#include <curl/curl.h>
#include <string.h>
#include <unistd.h>

#define ROOT_URL "http://meta.metaebene.me/media/cre/"
#define MAXNAME 10
#define MAXURL sizeof(ROOT_URL) + MAXNAME

void get_name(int n, char* name) {
  char* padding =
      n < 10  ? "00"
    : n < 100 ? "0"
    : "";

  sprintf(name, "cre%s%d.mp3", padding, n);
}

void get_url(int n, char* name, char* url) {

  strcpy(url, ROOT_URL);
  strcat(url, name);
}

FILE* get_relative_writestream(char* subdir, char* name) {
  FILE *fp;
  char cwd[PATH_MAX];
  char full_path[PATH_MAX];

  getcwd(cwd, sizeof(cwd));
  strcpy(full_path, cwd);
  strcat(full_path, subdir);
  strcat(full_path, name);
  fp = fopen(full_path, "wb");
  return fp;
}

size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
  size_t written = fwrite(ptr, size, nmemb, stream);
  return written;
}

int download_url(char* url, char* name, FILE* fp) {
  CURL *curl;
  CURLcode ret;
  curl = curl_easy_init();
  if (curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    ret = curl_easy_perform(curl);

    curl_easy_cleanup(curl);

    return ret;
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

  int ret = download_url(url, name, fp);
  if (ret != 0) printf("\t -- not found\n");

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
