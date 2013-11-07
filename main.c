#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "lib/cre_consts.h"
#include "lib/cre_limits.h"
#include "lib/strsplit.h"
#include "lib/download_url_buffer.h"
#include "lib/download_url_file.h"
#include "lib/get_links.h"

#define MIN(a,b) (((a)<(b))?(a):(b))

char* name_from_url(char* url) {
  char* parts[MAXPARTS];
  char *s = strdup(url);
  int len = strsplit(s, parts, "/");
  return parts[len -1];
}

void download_episode(char* url) {
  FILE *fp;
  char cwd[MAXPATH];
  char full_path[MAXPATH];
  char *name = name_from_url(url);

  getcwd(cwd, sizeof(cwd));
  sprintf(full_path, "%s/casts/%s", cwd, name);

  printf("downloading: %s to %s\n", url, full_path);

  fp = fopen(full_path, "w");
  long status = download_url_file(url, fp);
  if (status) printf("Download failed with status: %ld\n", status);
  fclose(fp);
}

int main(int argc, const char *argv[]) {
  char *links[MAXLINKS];
  int from_episode = 1;
  int to_episode = INT_MAX;
  if (argc > 1) from_episode = strtol(argv[1], NULL, 10);
  if (argc > 2) to_episode = strtol(argv[2], NULL, 10);

  DownloadResult res = download_url_buffer(ARCHIVE_URL);
  int len = get_links(res.html, links);
  to_episode = MIN(to_episode, len + 1);

  printf("Downloading episodes %d-%d\n", from_episode, to_episode);

  // adjust to 0 base
  from_episode--;
  to_episode--;

  for (int i = from_episode; i < to_episode; i++) {
    download_episode(links[i]);
  }

  return 0;
}
