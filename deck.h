struct card { int card_index; };
struct deck { int size; int current_deck[52]; };

struct deck * current_game;

char * cards[13];

int make_deck();

int draw_card();
