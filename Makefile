include config.mk

SRC = numint.c
OBJ = ${SRC:.c=.o}

all: numint

.c.o:
	${CC} -c ${CFLAGS} $<

${OBJ}: config.mk

numint: ${OBJ}
	${CC} -o $@ ${OBJ} ${LDFLAGS}

clean:
	rm -f numint ${OBJ}

.PHONY: all clean
