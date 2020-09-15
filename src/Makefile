OUTPUTFILENAME = binary
CC=clang
CFLAGS= -c -Wall
LFLAGS= -o $(OUTPUTFILENAME)

all: binary


main.o: main.c
				$(CC) $(CFLAGS) $^ -o $@

ip_maths.o: ip_maths.c

				$(CC) $(CFLAGS) $^ -o $@

binary: main.o ip_maths.o
				$(CC) $(LFLAGS) $^ -o $@


clean:
			rm *.o
