CC=cc
CFLAGS=-c -Wall
LDFLAGS=-lcurl

TAP=$(wildcard deps/tap/*.c)
TAP_OBJECTS=$(TAP:.c=.o)

FS_OBJECTS=deps/fs.o

LIB=$(wildcard lib/*.c)
LIB_OBJECTS=$(LIB:.c=.o)

TEST=$(wildcard test/*.c)
TEST_OBJECTS=$(TEST:.c=.o)
TEST_EXECUTABLES=$(TEST:.c=)

MAIN=main.c
MAIN_OBJECTS=$(MAIN:.c=.o)
EXECUTABLE=main

$(EXECUTABLE): $(LIB_OBJECTS) $(MAIN_OBJECTS) 
	$(CC) $(LDFLAGS) $^ -o $@

build-test-%: $(LIB_OBJECTS) $(FS_OBJECTS) $(TAP_OBJECTS)
	$(CC) $(LDFLAGS) test/$(subst build-test-,,$@).c $^ -o test/$(subst build-test-,,$@)

test-%: build-test-%
	test/$(subst test-,,$@)

test: $(subst test/,,$(addprefix build-test-,$(TEST_EXECUTABLES)))
	prove -e "$(PROVE_ENV)" $(PROVE_OPTIONS) $(TEST_EXECUTABLES)

testv: $(subst test/,,$(addprefix test-,$(TEST_EXECUTABLES)))

.c.o:
	$(CC) $(CFLAGS) $< -o $@

keep: $(FS_OBJECTS) $(TAP_OBJECTS)
clean: 
	rm -rf $(LIB_OBJECTS) $(MAIN_OBJECTS) $(EXECUTABLE) $(TEST_OBJECTS) $(TEST_EXECUTABLES) $(TAP_OBJECTS)

.PHONY: clean test testv keep build-test-% test-%
