all: tls clean

tls: main.o utilidades.o utilidades.h
	gcc -std=c99 -pthread -g -o tls main.o utilidades.o

main.o: main.c utilidades.h
	gcc -Wall -Wextra -g -c main.c

utilidades.o: utilidades.c utilidades.h
	gcc -Wall -Wextra -g -c utilidades.c

clean:
	rm -f *.o
