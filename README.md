# project02
## Project 2: The Final Frontier
## Maia Brydon, Ela Gulsen, Shafali Gupta, Michelle Tang (pd 5)

### Description
Our project is based on the card game, You’ve Got Crabs. Players break up into groups of two and try to win as many
crabs as possible.

To start, the team will get a secret signal which will indicate when a person has ‘crabs.’ In
the real-life game, the signal can be touching your nose or itching your eyebrow. In our version, it will be a secret
phrase/codeword that only the two members have access to. Each player then gets four cards and the objective
(to get ‘crabs’) is to have four of a kind (which is four of the same color - the game is played with a non-traditional deck).

The teammates must sit across from each other, forming two different sides. At any given time, only one side can play
(therefore only one of the players can be active). Meanwhile, the other side will be watching to see if the signal is
given. There will be four cards on the table. For the active side, the player will have the opportunity to switch any
card on the table with any card in their hand so that they can try and get four of a kind. They can make as many switches
as possible and when they are done, they place their hand down and the other side goes. If no switches are made on both
sides, then the four cards on the table are thrown back in the deck, and four new cards are drawn.

If a person has four of a kind, they will secretly signal their teammate. If the teammate sees the signal, they will call
out “You’ve got crabs!” and the team will be awarded a crab (point). If an opposing teammate sees the signal (having
correctly guesses what it is), that team will win the point instead. If “You’ve got crabs!” is prematurely called out,
meaning that the person does not have a four of a kind, that team will lose a crab (point).

After the point is awarded, the player gets four new cards from the deck. The game continues until there are no more crabs
to be given out.

Teammates are randomly assigned a secret signal to use with each other. When one partner has achieved crabs, they might transmit
words like “tomato”, “rose”, “apple”, and “heart”. To trick opponents, a partner could bluff by signaling “blueberry” when
they do not have crabs (which seems like it could fit into the “tomato”/”apple” pattern without more information).

### How to run this project:
- Find your IP address and type it into networking.h, LINE 19, #define TEST_IP [your ip here]
- Type 'make' into the terminal
- To run the server: ./server 4
- To run the clients: ./client, for each client that you listed would be playing when you declared the number of players. The game will not start until this number of players has joined.
- And you're done! Enjoy the game.

#### User commands: 
To make moves, type these commands:
- end : end your turn. Then you won't be able to swap cards, but there will be another player playing. 
- swap: You can swap any card from your hand with one of the  cards on the table. You will be prompeted after to give the index's of each card. 

### Bugs:
- The teams are hardcoded, as in you cannot pick your team member. The first two players that join (players 0 and 1) make up
team 1. Players 2 and 3 make up team 2.
- Players cannot make a custom signal between themselves, but rather are given a random signal that is the same as the one
given to their partner.
- Need to include your IP address in networking.h for the clients to connect properly
- Instead of the server maintaining one deck, the clients each have their own deck. 

