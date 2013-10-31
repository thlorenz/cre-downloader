#!/usr/bin/env sh

clib install thlorenz/gumbo-parser.c -o deps/gumbo-parser && \
clib install thlorenz/tap.c -o deps/tap && \
clib install jwerle/strsplit.h && \
clib install jwerle/fs.h
