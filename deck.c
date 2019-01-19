#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
struct card { int card_index; };
struct deck { int size; int current_deck[52]; };
struct table { int table_cards[4]; };

char * cards[13] = {"Crabrador Retriever", "Crabbi", "Jab Crab", "Taxi Crab", "Ab Crab", "Bunny Crabbit", "Shish Crabob", "Crabuccino", "King Crab", "Crabernet Sauvignon", "Low Crab Diet", "Crabaloupe", "Abracrabdabra"};

struct deck * current_game;
struct table * current_table;

/* Creates a deck that contains 4 instances of each card, randomly scattered throughout the deck.
 * Deck is stored in struct deck * current_game.
 */
int make_deck() {
    srand( time( NULL));
    int rand_index = (rand() % 13);
    current_game = malloc( sizeof(struct deck));
    current_game->size = 0;

    int cards_random[13];
    int i;
    for (i=0; i< 13; i++) {
        cards_random[i] = 4;
    }

    for (i=0; i<52; i++) {
        while (! cards_random[rand_index] ) rand_index = (rand() % 13);
        cards_random[ rand_index]--;
        current_game->current_deck[ current_game->size  ] = rand_index;
        current_game->size++;
        rand_index = (rand() % 13);
    }
    return 0;
}

/* Acts like a stack - decreases the size of the deck and returns a new card (represented as an integer.)
 * If the deck is out of cards, returns -1.
*/
int draw_card() {
    if (current_game->size == 0) return -1;
    current_game->size--;
    int new_card = current_game->current_deck[ current_game->size];
    return new_card;
}

/* Creates the table by drawing 4 cards from the deck. */
int create_table() {
    current_table = malloc(sizeof( struct table));
    for (int i=0; i<4; i++){
        current_table->table_cards[i] = draw_card();
    }
    return 0;
}

/* Prints the contents of the table. */
int print_table() {
    if (current_table->table_cards) {
      printf("----------------------------------------------------\n");
        printf("|   Cards on the table: \n|     ");
        for (int i=0; i<3; i++){
            printf("[%d] %s, ", i, cards[ current_table->table_cards[i]]);
        }
        printf("and [3] %s\n", cards[ current_table->table_cards[3]]);
          printf("----------------------------------------------------\n");
        return 0;
    }
    return -1;
}
