#ifndef GET_LINKS_H
#define GET_LINKS_H

#define ROOT_URL       "http://meta.metaebene.me/media/cre/"
#define ARCHIVE_URL    "http://cre.fm/archiv"
#define DOWNLOAD_URL   "http://meta.metaebene.me/media/cre/"

#define MAXPARTS 1024

#define MAXNAME 10
#define MAXURL sizeof(ROOT_URL) + MAXNAME
#define MAX_PATH 1024
#define MAX_LINKS 1024

int
get_links(char* links[]);

#endif
