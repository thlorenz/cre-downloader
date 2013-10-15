#include <stdio.h>
#include <string.h>

#include "download_url_buffer.h"
#include "../deps/gumbo-parser/gumbo.h"

#define ARCHIVE_URL "http://cre.fm/archiv"

static void
search_for_links(GumboNode* node) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      node->parent->v.element.tag == GUMBO_TAG_TD &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    printf("%s\n", href->value);
  }

  GumboVector* children = &node->v.element.children;
  for (int i = 0; i < children->length; ++i) {
    search_for_links((GumboNode*)(children->data[i]));
  }
}

int
get_links(char* links[]) {
  // TODO: this whole creating buffer over there and having to clean over here
  // doesn't seem very clean
  DownloadResult res = download_url_buffer(ARCHIVE_URL);

  GumboOutput* output = gumbo_parse(res.html);
  search_for_links(output->root);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  return 0;
}
