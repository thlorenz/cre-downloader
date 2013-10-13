#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "download_url_buffer.h"

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

int
find_tbody(char* html, int html_len) {
  return 0;
}

int
parse_links(char* html, int html_len, char* links[]) {
  char* _tbody = strstr(html, "<tbody>");
  char* tbody_ =  strstr(_tbody, "</tbody>");
  printf("res: %s\n", tbody_);
  return 0;
}

int
get_links(char* links[]) {
  //DownloadResult res;

  //res = download_url_buffer(ARCHIVE_URL);
  //if(res.status) return res.status;

  //parse_links(res.html, res.size, links);
  char* sample = get_sample();
  parse_links(sample, strlen(sample), links);

  //printf("html: %s\n", res.html);


  //if(res.html) free(res.html);
  return 0;
}
