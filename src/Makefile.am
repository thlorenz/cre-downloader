lib_LTLIBRARIES = libcre-downloader.la
libcre_downloader_la_SOURCES =  						\
	download_url.c download_url.h 						\
	download_url_file.c download_url_file.h
libcre_downloader_la_LDFLAGS = -lcurl

bin_PROGRAMS = main
main_SOURCES = main.c
main_LDADD = libcre-downloader.la
