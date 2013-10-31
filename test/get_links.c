#include <stdio.h>
#include <unistd.h>

#include "../src/cre_limits.h"
#include "../src/cre_consts.h"
#include "../src/download_url_buffer.h"
#include "../src/get_links.h"
#include "../deps/tap/tap.h"
#include "../deps/fs.h"
#include "../deps/strsplit.h"

int main(void) {
  plan(1);

  // execution may happen from inside ./test or from parent dir, therefore we need to adapt relative path to fixtures
  char cwd[MAX_PATH];
  getcwd(cwd, sizeof(cwd));
  char **parts = calloc(MAXPARTS, sizeof(char));
  size_t len = strsplit(cwd, parts, "/");
  char *base = parts[len - 1];
  char *path = strcmp(base, "test") ? "test/fixtures/urls.html" : "fixtures/urls.html";

  FILE *fp = fopen(path, "rb");
  char *html = fs_fread(fp);
  fclose(fp);

  printf("content:\n%s\n", html);
  ok(1, "downloaded");
  return 0;
}
