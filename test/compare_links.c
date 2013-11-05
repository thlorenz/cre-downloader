#include "../lib/compare_links.h"
#include "../deps/tap/tap.h"

int main(void) {
  plan(3);
  char *a, *b;

  a = "http:/some/thing/012-fdsf"; b = "http:/some/thing/112-fdsf";
  ok(compare_links(&a, &b) < 0, "012 comes before 112");

  a = "http:/some/thing/002-fdsf"; b = "http:/some/thing/002-fdsf";
  ok(compare_links(&a, &b) == 0, "002 same as 002");

  a = "http:/some/thing/202-fdsf"; b = "http:/some/thing/002-fdsf";
  ok(compare_links(&a, &b) > 0, "202 comes after 002");

  return 0;
}
