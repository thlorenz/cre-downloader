#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

static int get_episode(const char* s) {
  char c;
  int count = 0;
  int episode = 0;

  while((c = *(s++)) != '\0') {
    if (isdigit(c)) {
      count++;
      episode = episode * 10 + (c - '0');
    } else {
      episode = count = 0;
    }
    if (count == 3) return episode;
  }

  return 0;
}

int compare_links(const void* a, const void* b) {
  const char **ia = (const char **)a;
  const char **ib = (const char **)b;

  int ep1 = get_episode(*ia);
  int ep2 = get_episode(*ib);
  return ep1 - ep2;
}
