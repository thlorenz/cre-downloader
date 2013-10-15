#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lib/download_url_file.h"
#include "lib/get_links.h"

#define ROOT_URL "http://meta.metaebene.me/media/cre/"
#define MAXNAME 10
#define MAXURL sizeof(ROOT_URL) + MAXNAME
#define MAX_PATH 1024
#define MAX_LINKS 1024

void
get_url(int n, char* name, char* url) {

  strcpy(url, ROOT_URL);
  strcat(url, name);
}

FILE*
get_relative_writestream(char* subdir, char* name) {
  char cwd[MAX_PATH];
  char full_path[MAX_PATH];

  getcwd(cwd, sizeof(cwd));
  strcpy(full_path, cwd);
  strcat(full_path, subdir);
  strcat(full_path, name);
  return fopen(full_path, "wb");
}

void
get_name(int n, char* name) {
  char* padding =
      n < 10  ? "00"
    : n < 100 ? "0"
    : "";

  sprintf(name, "cre%s%d.mp3", padding, n);
}

void
download_episode(int n) {
  char name [MAXNAME];
  char url [MAXURL];
  FILE *fp;

  get_name(n, name);
  get_url(n, name, url);
  fp = get_relative_writestream("casts", name);

  printf("Downloading: %s\n", url);

  long status = download_url_file(url, fp);
  if (status) printf("Download failed with status: %ld\n", status);

  fclose(fp);
}


int main(int argc, const char *argv[])
{
  char* links[1024];
  int len = get_links(links);

  for (int i = 0; i < len; i++) {
    printf("link: %s", links[i]);
  }
  return 0;
}
