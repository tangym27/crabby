#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct card { int card_index; };
struct deck { int size; int current_deck[52]; };

char * cards[13] = {"Crabrador Retriever", "Crabbi", "Jab Crab", "Taxi Crab", "Ab Crab", "Bunny Crabbit", "Shish Crabob", "Crabuccino", "King Crab", "Crabernet Sauvignon", "Low Crab Diet", "Crabaloupe", "Abracrabdabra"};

struct deck * current_game;

int make_deck() {
    int rand_index = (rand() % 13);
    current_game = malloc( sizeof(struct deck));
    current_game->size = 0;
    
    int cards_random[13];
    int i;
    for (i=0; i< 13; i++) {
        cards_random[i] = 4;
    }
    
    for (i=0; i<52; i++) {
        rand_index = (rand() % 13);
        while (! cards_random[rand_index] ) { rand_index = (rand() % 13); }
        cards_random[ rand_index]--;
        current_game->current_deck[ current_game->size  ] = rand_index;
        current_game->size++;
    }
    
    return 0;
}

int draw_card() {
    current_game->size--;
    int new_card = current_game->current_deck[ current_game->size];
    return new_card;
}

int main() {
    srand( time(NULL));
    make_deck();
    for (int i; i<52; i++){
        printf("%s\n", cards[ draw_card()]);
    }
    return 0;
}
