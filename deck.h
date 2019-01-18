struct card { int card_index; };
struct deck { int size; int current_deck[52]; };
struct table { int table_cards[4]; };

struct deck * current_game;
struct table * current_table;

char * cards[13];

int make_deck();

int draw_card();

int create_table();
int print_table();
char * random_m(int num);
