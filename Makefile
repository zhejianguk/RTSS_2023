CC = gcc

OFLAGS := -O3
CFLAGS:= -O3

CFLAGS_CM:= -O3

dbf: dbf.c
	${CC} ${CFLAGS} -c dbf.c

sched_test: sched_test.c
	${CC} ${CFLAGS} -o sched_test.elf sched_test.c dbf.o 

clean:
	rm -f *.o *.elf *.so
