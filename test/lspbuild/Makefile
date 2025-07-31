
CC = clang

CFLAGS = -Wall -Wextra -pedantic -std=c89
OPT = -O3 -pipe -march=native

SRC = lib.c app.c
OBJ = ${SRC:.c=.o}

DEPS = ${SRC} lib.h


all: app
	./Compdb


.c.o:
	${CC} -c ${CFLAGS} ${OPT} $< -MJ $@.json

${OBJ}: ${DEPS}



app: $(OBJ)
	${CC} -o $@ ${OBJ}

clean:
	rm *.o*
	rm app

