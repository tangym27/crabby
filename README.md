# project02
Project 2: The Final Frontier
Maia Brydon, Ela Gulsen, Shafali Gupta, Michelle Tang

How to run this project:
- Find your IP address and type it into networking.h, LINE 19, #define TEST_IP [your ip here]
- Type 'make' into the terminal
- To run the server: ./server 4
- To run the clients: ./client, for each client that you listed would be playing when you declared the number of players. The game will not start until this number of players has joined.
- And you're done! Enjoy the game.

Bugs:
- The teams are hardcoded, as in you cannot pick your team member. The first two players that join (players 0 and 1) make up
team 1. Players 2 and 3 make up team 2.
- Players cannot make a custom signal between themselves, but rather are given a random signal that is the same as the one
given to their partner.
- Need to include your IP address in networking.h for the clients to connect properly

