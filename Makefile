COPT = -Wall -Wextra -ansi -pedantic -ggdb

all: libbits.a obligatorio1

obligatorio1: obligatorio1.o libbits.a
	cc $(COPT) -o $@ obligatorio1.o -L./ -lbits

.c.o:
	cc $(COPT) -c $<

libbits.a: bits.o
	ar rcs $@ $<

clean:
	rm -f *.o *.a obligatorio1
