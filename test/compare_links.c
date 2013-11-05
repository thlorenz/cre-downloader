#include "../lib/compare_links.h"
#include "../deps/tap/tap.h"


int main(void) {
  plan(3);
  ok(compare_links("http:/some/thing/012-fdsf", "http:/some/thing/112-fdsf") < 0, "012 comes before 112");
  ok(compare_links("http:/some/thing/002-fdsf", "http:/some/thing/002-fdsf") == 0, "002 same as 002");
  ok(compare_links("http:/some/thing/202-fdsf", "http:/some/thing/002-fdsf") > 0, "202 comes after 002");

  return 0;
}
