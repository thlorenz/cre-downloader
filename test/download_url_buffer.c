#include <stdio.h>
#include "../src/download_url_buffer.h"
#include "../deps/tap/tap.h"

int main(void)
{
  plan(2);
  const char *url = "https://raw.github.com/thlorenz/cre-downloader/master/README.md";
  const char *buffer;

  DownloadResult res = download_url_buffer(url);
  // TODO: failing case -- (aborted by callback)
  cmp_ok(res.status, "==", 200, "returns status 200");
  ok(res.size, "has non-zero size");
  like(res.html, "cre-downloader", "downloaded README has same content as local README");


  return 0;
}
