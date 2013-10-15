#include <string.h>
#include <stdio.h>

int path_split(char* path, const char* sep, const char* parts[]) {
  int i = 0;
  char *pc;
  pc = strtok(path, sep);

  while (NULL != pc) {
    parts[i++] = pc;
    pc = strtok(NULL, sep);
  }
  return i;
}
