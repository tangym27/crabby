# all: player.o deck.o networking.o select_server.c
# 	gcc -o client player.o deck.o networking.o
# 	gcc -o server networking.c select_server.c
#
# player.o: player.c deck.h networking.h
# 	gcc -c player.c
#
# deck.o: deck.c
# 	gcc -c deck.c
#
# networking.o: networking.c
# 	gcc -c networking.c
#
# select_server.o: select_server.c
# 	gcc -c select_server.c
# run:
# 	./a.out
#
# clean:
# 	rm a.out
# 	rm *.o

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
