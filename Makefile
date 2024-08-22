CC := gcc
CFLAGS := -Wextra -Wall -ggdb -Iinclude
LIBS := -Llib -lraylib -lm

thing: src/*.c
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}
