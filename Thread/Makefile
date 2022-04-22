CC      = gcc

CFLAGS  = -Wall -Wextra -Werror
CFLAGS += -g

LDFLAGS = -pthread

TOUS := aleazard compteur-gc rdv

tout: ${TOUS}

aleazard: aleazard.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

exo1 : Exo1.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

exo2 : Exo2.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

exo3 : Exo3.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

exo4 : Exo4.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

compteur-gc: compteur-gc.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

rdv: rdv.c
	${CC} ${CFLAGS} $< -o $@ ${LDFLAGS}

clean:
	rm -f core *.o

realclean: clean
	rm -f ${TOUS} exo1 Exo2 exo2 exo3 test test2

.PHONY: all clean realclean
