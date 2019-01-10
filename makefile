all: player.o deck.o
	gcc player.o deck.o

player.o: player.c deck.h
	gcc -c player.c

deck.o: deck.c
	gcc -c deck.c
	
run:
	./a.out
