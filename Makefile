#minimake: main.c pretreatment.c parser.c graph.c assistfun.c
#	gcc -o minimake main.c pretreatment.c parser.c graph.c assistfun.c
out: 1.o 2.o 3.o

	gcc -o out 1.o 2.o 3.o
1.o: 1.c
	gcc -c 1.c
2.o: 2.c 
	gcc -c 2.c
3.o: 3.c
	gcc -c 3.c

