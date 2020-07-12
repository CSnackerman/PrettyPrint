CC = gcc
CFLAGS = -g -std=c99
target = test
sources = test.c pretty_printer.c

$(target) : $(sources)

clean :
	rm -f *.o $(target)