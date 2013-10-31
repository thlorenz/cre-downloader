#include <stdio.h>
#include "../src/download_url_file.h"
#include "../deps/tap/tap.h"
#include "../deps/fs.h"

int main(void) {
  plan(2);

  const char *downloaded = "__remote_readme__.md";
  unlink(downloaded);

  const char *url = "https://raw.github.com/thlorenz/cre-downloader/master/README.md";
  FILE *fp;

  char *remote = 0;
  int remote_len, status;

  // Download
  fp = fopen(downloaded, "wb");
  status = download_url_file(url, fp);
  fclose(fp);

  cmp_ok(status, "==", 200, "returns status 200");

  // Read downloaded README
  fp = fopen(downloaded, "r");

  remote_len = fs_fsize(fp);
  remote = malloc(remote_len);
  fread(remote, 1, remote_len, fp);
  fclose(fp);

  unlink(downloaded);

  like(remote, "cre-downloader", "downloaded README has same content as local README");

  return 0;
}
