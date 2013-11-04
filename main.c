#include <stdio.h>
#include "lib/download_url_file.h"

int main(void) {
  const char *url = "https://github.com/thlorenz/cre-downloader/raw/master/lib/download_url_file.c";
  const FILE *fp = fopen("test.c", "wb");
  download_url_file(url, fp);
  return 0;
}
