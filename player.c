#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "deck.h"

struct team { int team_no; int points; };
struct player { char * username; int hand[4]; int partner; struct team * p_team; int is_turn;};

//int create_player(int id, 


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

/* Given a struct * player, adds a point to the player's team.
 * Returns -1 if the player has no team.
 * Else, returns 0.
 */
int add_point( struct player * plyr) {
    if (plyr->p_team) plyr->p_team->points++;
    else return -1;
    return 0;
}

/* Given a struct * player, checks if the player's hand contains crabs.
 * Returns 0 if no crabs. Returns 1 if crabs.
 */
int check_crabs( struct player * plyr) {
    int card_check = plyr->hand[0];
    for (int i=1; i<4; i++){
        if ( card_check != plyr->hand[i] ) return 0;
    }
    return 1;
}

/* Given a struct player *, prints the player's hand. */
int print_hand( struct player * plyr) {
    if (plyr) {
        printf("Cards in %s's hand: \n", plyr->username);
        for (int i=0; i<3; i++){
            printf("[%d] %s, ", i, cards[ plyr->hand[i]]);
        }
        printf("and [3] %s\n", cards[ plyr->hand[3]]);
        return 0;        
    }
    return -1;
}

int main() {
    srand( time(NULL));

    struct player * me = malloc( sizeof(struct player) );
    struct player * you = malloc( sizeof(struct player) );
    make_deck();
    
    /*printf("THE DECK:\n");
    for (int l = 0; l <52; l++) {
        printf("%s\n", cards[current_game->current_deck[l]]);
    }*/
    
    printf("YOUR HAND:\n");
    make_hand( me);
    print_hand( me);
    
    printf("\n\nYOUR TEAMMATE'S HAND:\n");
    make_hand( you);
    print_hand( you);
    
    struct team * crabby = malloc( sizeof(struct team));
    crabby->team_no = 17;
    
    me->p_team = crabby;
    you->p_team = crabby;
    
    add_point(me);
    printf("\ncrabby team points: %d\n", crabby->points);
    add_point(you);
    printf("\ncrabby team points: %d\n", crabby->points);
    
    printf("%d\n", check_crabs(me));
    
    create_table();
    print_table();
}
