#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "get_links.h"
#include "download_url_buffer.h"
#include "path_split.h"
#include "../deps/gumbo-parser/gumbo.h"

static void
to_download_url(const char* archive_url, char* download_url) {
  const char* parts[MAXPARTS];
  char *s = strdup(archive_url);
  int len = path_split(s, "/", parts);
  sprintf(download_url, "%s%s.mp3", DOWNLOAD_URL, parts[len - 1]);
}

static int
search_for_links(GumboNode* node, char* links[], int current) {
  int n = current;

  if (node->type != GUMBO_NODE_ELEMENT) {
    return n;
  }

  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      node->parent->v.element.tag == GUMBO_TAG_TD &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    links[n] = malloc(sizeof(char) * MAXURL);
    strcpy(links[n], href->value);
    n++;
  }

  GumboVector* children = &node->v.element.children;
  for (int i = 0; i < children->length; ++i) {
    n = search_for_links((GumboNode*)(children->data[i]), links, n);
  }
  return n;
}

static int
search_for_links_test(char* links[]) {
  int i;
  for (int i = 0; i < 10; i++) {
    links[i] = malloc(MAXURL);
    sprintf(links[i], "%s/cre_00%d", ARCHIVE_URL, i);
  }
  return i;
}

int
get_links(char* links[]) {
  char* arch_links[MAX_LINKS];

  // TODO: this whole creating buffer over there and having to clean over here
  // doesn't seem very clean
  DownloadResult res = download_url_buffer(ARCHIVE_URL);

  GumboOutput* output = gumbo_parse(res.html);

  int len = search_for_links(output->root, arch_links, 0);
  gumbo_destroy_output(&kGumboDefaultOptions, output);

  for (int i = 0; i < len; i++) {
    links[i] = malloc(MAXURL);
    to_download_url(arch_links[i], links[i]);
  }
  return len;
}
