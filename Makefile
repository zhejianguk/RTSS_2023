CC = gcc

OFLAGS := -O3
CFLAGS:= -O3

CFLAGS_CM:= -O3

bound: bound.c
	${CC} ${CFLAGS} -c bound.c -lm

task_gen: task_gen.c
	${CC} ${CFLAGS} -o task_gen.elf task_gen.c -lm 


min_budget: min_budget.c
	${CC} ${CFLAGS} -c min_budget.c -lm

main: main.c
	${CC} ${CFLAGS} -o main.elf main.c bound.o min_budget.o -lm


clean:
	rm -f *.o *.elf *.so
