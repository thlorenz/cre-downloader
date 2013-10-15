#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "download_url_buffer.h"
#include "path_split.h"
#include "../deps/gumbo-parser/gumbo.h"

#define ARCHIVE_URL "http://cre.fm/archiv"
#define DOWNLOAD_URL "http://meta.metaebene.me/media/cre/"
#define MAXPARTS 1024

static void
to_archive_url(const char* url, char* archive_url) {
  const char* parts[MAXPARTS];
  char* path = strdup(url);
  int len = path_split(path, "/", parts);

  // last part is the name we want -- TODO: what if no part found?
  sprintf(archive_url, "%s%s.mp3", DOWNLOAD_URL, parts[len - 1]);
  free(path);
}

static int
search_for_links(GumboNode* node, char* links[], const int current) {
  int i = current;
  if (node->type != GUMBO_NODE_ELEMENT) {
    return i;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
      node->parent->v.element.tag == GUMBO_TAG_TD &&
      (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
    to_archive_url(href->value, links[i++]);
  }

  GumboVector* children = &node->v.element.children;
  for (int i = 0; i < children->length; ++i) {
    search_for_links((GumboNode*)(children->data[i]), links, i);
  }
  return i;
}

int
get_links(char* links[]) {
  // TODO: this whole creating buffer over there and having to clean over here
  // doesn't seem very clean
  DownloadResult res = download_url_buffer(ARCHIVE_URL);

  GumboOutput* output = gumbo_parse(res.html);

  int len = search_for_links(output->root, links, 0);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  return len;
}
