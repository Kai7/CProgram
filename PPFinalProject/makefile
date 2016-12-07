# declare variables
CC = g++
CFLAGS = -std=c++11


main_fpgrowth:main_fpgrowth.o fptree.o
	$(CC) $(CFLAGS) main_fpgrowth.o fptree.o -o main_fpgrowth
main_fpgrowth.o:main_fpgrowth.cpp fptree.h fptree.cpp
	$(CC) $(CFLAGS) -c main_fpgrowth.cpp
fptree.o:fptree.h fptree.cpp
	$(CC) $(CFLAGS) -c fptree.cpp

clean:
	rm -f main_fpgrowth main_fpgrowth.o fptree.o
