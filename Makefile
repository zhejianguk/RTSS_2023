CC = gcc

OFLAGS := -O3
CFLAGS:= -O3

CFLAGS_CM:= -O3

sched: sched.c
	${CC} ${CFLAGS} -o sched.elf sched.c -lpthread


clean:
	rm -f *.o *.elf *.so
