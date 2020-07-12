CC = gcc
CFLAGS = -g -std=c99
target = test
sources = *.c

$(target) : $(sources)

clean :
	rm -f *.o $(target)