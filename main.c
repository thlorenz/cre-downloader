#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "./lib/download_url.h"

#define ROOT_URL "http://meta.metaebene.me/media/cre/"
#define MAXNAME 10
#define MAXURL sizeof(ROOT_URL) + MAXNAME
#define MAX_PATH 1024

void get_url(int n, char* name, char* url) {

  strcpy(url, ROOT_URL);
  strcat(url, name);
}

FILE* get_relative_writestream(char* subdir, char* name) {
  char cwd[MAX_PATH];
  char full_path[MAX_PATH];

  getcwd(cwd, sizeof(cwd));
  strcpy(full_path, cwd);
  strcat(full_path, subdir);
  strcat(full_path, name);
  return fopen(full_path, "wb");
}

void get_name(int n, char* name) {
  char* padding =
      n < 10  ? "00"
    : n < 100 ? "0"
    : "";

  sprintf(name, "cre%s%d.mp3", padding, n);
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
  // can still see this function here although it is static
  // write_data();

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
