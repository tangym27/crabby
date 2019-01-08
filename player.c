#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

struct team { int team_no; int points; };
struct player { char * username; int hand[4]; int partner; struct team * p_team;};

/* Makes a hand by drawing 4 cards.
 * If the deck is out of cards, returns -1.
 * Else, returns 0.
 */
int make_hand( struct player * plyr) {
    for (int i = 0; i<4; i++) {
        int new_card = draw_card();
        if (new_card == -1) return -1;
        plyr->hand[i] = new_card;
    }
    return 0;
}

int main() {
    srand( time(NULL));

    struct player * me = malloc( sizeof(struct player) );
    make_deck();
    
    printf("THE DECK:\n");
    for (int l = 0; l <52; l++) {
        printf("%s\n", cards[current_game->current_deck[l]]);
    }
    
    printf("\n\nYOUR HAND:\n");
    if (make_hand( me) > -1) {
        for (int i= 0; i<4; i++) printf("%s\n", cards [me->hand[i]]);
    }
}
