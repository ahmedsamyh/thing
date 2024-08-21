CC := gcc
CFLAGS := -Wextra -Wall -ggdb -Iinclude
LIBS := -Llib -lraylib -lm

thing: src/thing.c
	${CC} ${CFLAGS} -o $@ $^ ${LIBS}
