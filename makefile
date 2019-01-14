all: player.o deck.o networking.o
	gcc player.o deck.o networking.o

player.o: player.c deck.h networking.h
	gcc -c player.c

deck.o: deck.c
	gcc -c deck.c

networking.o: networking.c
	gcc -c networking.c
run:
	./a.out
