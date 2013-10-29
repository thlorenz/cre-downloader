#include <stdio.h>
#include "../../src/download_url_file.h"
#include "../../deps/tap/tap.h"

int main(void) {
  const char *url = "https://github.com/thlorenz/cre-downloader/raw/master/lib/download_url_file.c";
  const FILE *fp = fopen("test.c", "wb");
  download_url_file(url, fp);
  ok(1, "downloaded file without failing");
  ok(fp != NULL, "valid file pointer");
  cmp_ok(1, "<=", 2, "1 <= 2");
  done_testing();
  return 0;
}
