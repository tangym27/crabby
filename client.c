#include "networking.h"
#include "player.h"
#include "deck.h"

int check_buffer(char * buffer, int size, int crab_deck[]){
  if (strcmp(buffer, "end") == 0){
    printf("(end happened)\n" );
    return 0;
  }
  else if (strcmp(buffer, "print") == 0)
    return 0;
  else{
    int i = atoi(buffer);
    if (i == 0)
      return 1;
    else{
      if (i > size-1)
	return 1;
      else if (crab_deck[i] == 0)
	return 1;
      else
	return 0;
    }
  }
}

int main(int argc, char **argv) {
  int size = 1000;
  int crab_deck[51];
  int server_socket;
  char buffer[BUFFER_SIZE];

  if (argc == 2)
    server_socket = client_setup( argv[1]);
  else
    server_socket = client_setup( TEST_IP );

  printf("Still missing people. MICHELLE THIS WILL NOT START.\n");
  read(server_socket, buffer, sizeof(buffer));
 //  crab_deck[size++] = 1;
 //  char * cards = calloc(250, sizeof(char));
 //  strcpy(cards, buffer);
 //  int i;
 //  for (i = 0; i < 4; i++) {
 //    char * tmp = strsep(&cards, "-");
 //    crab_deck[size++] = atoi(tmp);
 // }

  printf("\n\nGAME HAS STARTED SHOULD HAVE ENOUGH CLIENTS MICHELLE GET IT TOGETHER!\n\n");
  while (1) {
    printf("It is not your turn yet.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      if (strcmp(buffer, ACK)) {
        printf("received: [%s]\n", buffer);
      }
      else break;
    }

    printf("What would you like your username to be?\n");
    char * response = malloc(256);
    fgets(response, 200, stdin);
    int my_player = create_player(response);
    make_deck();

    printf("YOUR HAND:\n");
    make_hand( my_player);
    print_hand( my_player);

    create_table();
    print_table();

    printf("\n");
    if (swap_cards(0, 1, 1) == -2) printf("Hey! It's not your turn. No switch was made.\n");

    //while the player didn't say they wanted to end their turn
	printf("check"); 
      while(check_buffer(buffer, size, crab_deck)){
      printf("Would you like to switch any cards? y/n \n");
      char * switch_res = malloc(256);
      fgets(switch_res, 200, stdin);
      if (response[0] == 'y'){
        printf("which cards would you like to switch? Type the card number from your hand\n");
        char * hand_res= malloc(256);
        fgets(hand_res, 200, stdin);
        printf("Type the card number from the deck\n");
        char * deck_res = malloc(256);
        fgets(deck_res, 200, stdin);
        swap_cards(buffer,hand_res, deck_res); 
     printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      //*strchr(buffer, '\n') = 0;
      }
    }
    printf("your turn has ended.\n");

    write(server_socket, buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);
    read(server_socket, buffer, sizeof(buffer));
    //   //printf("buffer:%s\n", buffer);
    //   int id = atoi(buffer);
    // //  printf("Card name: %s\n",get_card_name(catalog, id) );
      char * name = calloc(50, sizeof(char));
      name = "boop";
      sprintf(buffer, "Drew the %s card.\n", name);
    //   //if (strcmp(name, "Exploding Kitten")){
      memset(buffer, 0, BUFFER_SIZE);
     strcpy(buffer, "drew");
      write(server_socket, buffer, sizeof(buffer));
      printf("BUGGER: %s\n",buffer );
      //crab_deck[size] = atoi(buffer);
      size++;
    //  }
  }
}
