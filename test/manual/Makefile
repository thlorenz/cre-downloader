CC=gcc
CFLAGS=-c -Wall -std=c99
LDFLAGS=-lcurl
SOURCES=test_download_url_file.c $(wildcard ../../lib/*.c) $(wildcard ../../deps/**/*.c)
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test_download_url_file

.phony: all clean

all: clean $(SOURCES) $(EXECUTABLE)

start: all
	./test_download_url_file

clean: 
	rm -rf $(EXECUTABLE)
	rm -rf $(OBJECTS)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
