all: player.o deck.o networking.o select_server.c
	gcc -o client player.o deck.o networking.o
	gcc -o server networking.c select_server.c

player.o: player.c deck.h networking.h
	gcc -c player.c

deck.o: deck.c
	gcc -c deck.c

networking.o: networking.c
	gcc -c networking.c
	
select_server.o: select_server.c
	gcc -c select_server.c
run:
	./a.out

clean:
	rm a.out
	rm *.o
