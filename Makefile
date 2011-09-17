CC = gcc
CFLAGS = -pedantic -Wall -g -I../..
LDFLAGS = -L../.. -lspnav -lxdo -lX11

.PHONY: all
all: spacemouse

spacemouse: spacemouse.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
.PHONY: clean
clean:
	rm -f spacemouse
