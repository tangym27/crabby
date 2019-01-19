all: client server

server: server.o networking.o deck.o
	gcc -g -o server server.o networking.o deck.o

client: client.o networking.o player.o deck.o
	gcc -g -o client client.o networking.o player.o deck.o

client.o: client.c player.c networking.h player.h deck.h
	gcc -g -c client.c

server.o: server.c player.c networking.h deck.h
	gcc -g -c server.c

networking.o: networking.c networking.h
	gcc -g -c networking.c

run: player
	./player

player: player.c player.h deck.h
	gcc -g -o player player.c deck.o

clean:
	rm *.o
	rm *~
