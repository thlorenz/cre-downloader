#include <stdlib.h>
#include <string.h>

#include "../deps/gumbo-parser/gumbo.h"

#include "cre_consts.h"
#include "cre_limits.h"
#include "get_links.h"
#include "download_url_buffer.h"
#include "compare_links.h"
#include "strsplit.h"

static void qsort_links(char** links, int len) {
  qsort(links, len, sizeof(char *), compare_links);
}

static void to_download_url(char* url) {
  char* parts[MAXPARTS];
  int n = strsplit(url, parts, "/");
  strcpy(url, DOWNLOAD_URL);
  strcat(url, parts[n - 1]);
  strcat(url, ".mp3");
}

static int search_for_links(const GumboNode* node, char* links[], int current) {
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

  const GumboVector* children = &node->v.element.children;
  for (int i = 0; i < children->length; ++i) {
    n = search_for_links((GumboNode*)(children->data[i]), links, n);
  }
  return n;
}

int get_links(const char* html, char* links[]) {
  GumboOutput* gum = gumbo_parse(html);
  int len = search_for_links(gum->root, links, 0);
  for (int i = 0; i < len; i++) to_download_url(links[i]);

  qsort_links(links, len);

  return len;
}
