# paths
PREFIX = /usr/local
MANPREFIX = ${PREFIX}/share/man
LIBS = -lm

# flags
CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS   = -g -std=c99 -pedantic -Wall -Os ${CPPFLAGS}
LDFLAGS  = ${LIBS}

CC = cc
