include config.mk

SRC = numint.c
OBJ = ${SRC:.c=.o}
TARG = ${SRC:.c=}

all: ${TARG}

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

${TARG}: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f ${TARG} ${OBJ}

.PHONY: all clean
