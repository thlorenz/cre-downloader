#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "../lib/cre_limits.h"
#include "../lib/cre_consts.h"
#include "../lib/download_url_buffer.h"
#include "../lib/get_links.h"
#include "../lib/strsplit.h"
#include "../deps/tap/tap.h"
#include "../deps/fs.h"

int main(void) {
  plan(3);

  // execution may happen from inside ./test or from parent dir, therefore we need to adapt relative path to fixtures
  char cwd[MAXPATH];
  getcwd(cwd, sizeof(cwd));
  char **parts = calloc(MAXPARTS, sizeof(char));
  size_t nparts = strsplit(cwd, parts, "/");
  char *base = parts[nparts - 1];
  char *path = strcmp(base, "test") ? "test/fixtures/urls.html" : "fixtures/urls.html";

  FILE *fp = fopen(path, "rb");
  char *html = fs_fread(fp);
  fclose(fp);

  char* links[MAXLINKS];
  int len = get_links(html, links);
  ok(len > 200, "gets more than 200 links");

  is(links[0], "http://meta.metaebene.me/media/cre/cre001", "first link is cre001");
  is(links[9], "http://meta.metaebene.me/media/cre/cre010-regine-debatty", "10th link is cre010-regine-debatty");

  return 0;
}
