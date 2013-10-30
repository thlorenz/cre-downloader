#include <stdio.h>
#include "../src/download_url_file.h"
#include "../deps/tap/tap.h"

int file_len(FILE *fp) {
  int len;
  fseek(fp, 0, SEEK_END);
  len = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  return len;
}

int main(void) {
  plan(1);

  const char *downloaded = "__remote_readme__.md";
  unlink(downloaded);

  const char *url = "https://raw.github.com/thlorenz/cre-downloader/master/README.md";
  FILE *fp;

  char *remote = 0;
  int remote_len;

  // Download
  fp = fopen(downloaded, "wb");
  download_url_file(url, fp);
  fclose(fp);

  // Read downloaded README
  fp = fopen(downloaded, "r");
  remote_len = file_len(fp);
  remote = malloc(remote_len);
  fread(remote, 1, remote_len, fp);
  fclose(fp);

  unlink(downloaded);

  like(remote, "cre-downloader", "downloaded README has same content as local README");

  return 0;
}
