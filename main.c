#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "lib/download_url_file.h"
#include "lib/get_links.h"
#include "lib/path_split.h"

void
get_url(int n, char* name, char* url) {
  strcpy(url, ROOT_URL);
  strcat(url, name);
}

char*
name_from_url(char* url) {
  const char* parts[MAXPARTS];
  char *s = strdup(url);
  int len = path_split(s, "/", parts);
  return (char*)parts[len -1];
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
download_episode(char* url) {
  FILE *fp;
  char *name;

  name = name_from_url(url);
  printf("downloading: %s to %s\n", url, name);
  fp = get_relative_writestream("casts", name);

  printf("Downloading: %s\n", url);

  long status = download_url_file(url, fp);
  if (status) printf("Download failed with status: %ld\n", status);

  fclose(fp);
}

int main(int argc, const char *argv[])
{
  char* links[MAX_LINKS];
  int len = get_links(links);

  printf("Got %d links", len);
  for (int i = len - 11; i >= 33; i--) {
    download_episode(links[i]);
  }

  return 0;
}
