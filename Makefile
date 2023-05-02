CC = gcc

OFLAGS := -O3
CFLAGS:= -O3

CFLAGS_CM:= -O3

bound: bound.c
	${CC} ${CFLAGS} -c bound.c -lm

task_gen: task_gen.c
	${CC} ${CFLAGS} -o task_gen.elf task_gen.c -lm 

main: main.c
	${CC} ${CFLAGS} -o main.elf main.c bound.o -lm


clean:
	rm -f *.o *.elf *.so
