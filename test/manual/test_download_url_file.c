#include <stdio.h>
#include "../../lib/download_url_file.h"
#include "../../deps/tap/tap.h"

int main(void) {
  plan(3);
  const char *url = "https://github.com/thlorenz/cre-downloader/raw/master/lib/download_url_file.c";
  const FILE *fp = fopen("test.c", "wb");
  download_url_file(url, fp);
  ok(1, "downloaded file without failing");
  ok(fp != NULL, "valid file pointer");
  cmp_ok(1, "<=", 2, "1 <= 2");
  return 0;
}

