#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "download_url_buffer.h"
#include "../deps/gumbo-parser/gumbo.h"

#define ARCHIVE_URL "http://cre.fm/archiv"
#define IN 1;
#define OUT 0;

char* get_sample () {
  return "<html><p>Other stuff</p>"
  "<tbody>														<tr class=\"podcast_archive_element\">"
  "  <td class=\"thumbnail\"><img src=\"http://meta.metaebene.me/media/cre/cre203-online-journalismus.jpg\" style=\"height: 96px; width: 96px;\" />"
  "        </td>"
  "  <td class=\"date\">"
  "    <span class=\"release_date\">16.08.2013</span>"
  "  </td>"
  "  <td class=\"title\">"
  "    <a href=\"http://cre.fm/cre203-online-journalismus\"><strong>CRE203 Online-Journalismus</strong></a><br>Die Digitalisierung ändert die Vorzeichen der journalistischen Berichterstattung"
  "</td>"
  "  <td class=\"duration\">"
  "    02:16:00"
  "  </td>"
  "</tr>														<tr class=\"podcast_archive_element\">"
  "  <td class=\"thumbnail\"><img src=\"http://meta.metaebene.me/media/cre/cre202-hackerfilme.jpg\" style=\"height: 96px; width: 96px;\" />"
  "        </td>"
  "  <td class=\"date\">"
  "    <span class=\"release_date\">30.03.2013</span>"
  "  </td>"
  "  <td class=\"title\">"
  "    <a href=\"http://cre.fm/cre202-hackerfilme\"><strong>CRE202 Hackerfilme</strong></a><br>Das Bild des Hackers in der Filmkultur"
  "</td>"
  "  <td class=\"duration\">"
  "    03:10:15"
  "  </td>"
  "</tr>														<tr class=\"podcast_archive_element\">"
  "  <td class=\"thumbnail\"><img src=\"http://meta.metaebene.me/media/cre/cre201-hoehlenforschung.jpg\" style=\"height: 96px; width: 96px;\" />"
  "        </td>"
  "  <td class=\"date\">"
  "    <span class=\"release_date\">13.03.2013</span>"
  "  </td>"
  "  <td class=\"title\">"
  "    <a href=\"http://cre.fm/cre201-hoehlenforschung\"><strong>CRE201 Höhlenforschung</strong></a><br>Über Entdeckung und Schutz der letzten unbekannten Orte der Welt"
  "</td>"
  "  <td class=\"duration\">"
  "    02:40:19"
  "  </td>"
  "</tr>														<tr class=\"podcast_archive_element\">"
  "  <td class=\"thumbnail\"><img src=\"http://meta.metaebene.me/media/cre/cre200-stadtplanung.jpg\" style=\"height: 96px; width: 96px;\" />"
  "        </td>"
  "  <td class=\"date\">"
  "    <span class=\"release_date\">05.02.2013</span>"
  "  </td>"
  "  <td class=\"title\">"
  "    <a href=\"http://cre.fm/cre200-stadtplanung\"><strong>CRE200 Stadtplanung</strong></a><br>Die Geschichte der Stadt und die Herausforderung ihrer Gestaltung in der Gegenwart"
  "</td>"
  "  <td class=\"duration\">"
  "    03:16:38"
  "  </td>"
  "</tr>"
  "</tbody>";
}

static void
search_for_links(GumboNode* node) {
  if (node->type != GUMBO_NODE_ELEMENT) {
    return;
  }
  GumboAttribute* href;
  if (node->v.element.tag == GUMBO_TAG_A &&
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
  char* contents = get_sample();

  GumboOutput* output = gumbo_parse(contents);
  search_for_links(output->root);
  gumbo_destroy_output(&kGumboDefaultOptions, output);
  return 0;
}
