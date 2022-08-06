CC=cc
CFLAGS=-Wall -Wextra -Wshadow -pedantic -O2 -ansi

all: dns-server

dns-server: dns-server.c strmap.c strmap.h
	$(CC) $(CFLAGS) -o $@ $^
