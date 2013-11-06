#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "lib/cre_consts.h"
#include "lib/cre_limits.h"
#include "lib/strsplit.h"
#include "lib/download_url_buffer.h"
#include "lib/download_url_file.h"
#include "lib/get_links.h"

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
  sprintf(full_path, "%s/casts/%s.mp3", cwd, name);

  printf("downloading: %s to %s\n", url, full_path);

  fp = fopen(full_path, "w");
  long status = download_url_file(url, fp);
  if (status) printf("Download failed with status: %ld\n", status);
  fclose(fp);
}

int main(void) {
  char *links[MAXLINKS];

  DownloadResult res = download_url_buffer(ARCHIVE_URL);
  int len = get_links(res.html, links);

  for (int i = 0; i < len; i++) {
    download_episode(links[i]);
  }

  return 0;
}
