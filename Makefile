CC = gcc
INCLUDE = include/
LIBS = -lm
CFLAGS = -Wall -g

OBJECTS = \
	main.o


flgfx: ${OBJECTS}
	${CC} ${CFLAGS} -o $@ ${OBJECTS} ${LIBS}

clean:
	rm -rf *.o
	rm -rf flgfx

%.o: src/%.c
	${CC} ${CFLAGS} -c $<
