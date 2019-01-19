#include "networking.h"
#include "player.h"
#include "deck.h"
#include <stdio.h>
#include <time.h>

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
  make_deck();
    
  int size = 1000;
  int crab_deck[51];
  int server_socket;
  char buffer[BUFFER_SIZE];
  char username[100];
  //char ** catalog = create_catalog(&cat_size);

  if (argc == 2)
  server_socket = client_setup( argv[1]);
  else
  server_socket = client_setup( TEST_IP );

  printf("\e[1;1H\e[2J\n\n");
  printf("Welcome to 'Why So \033[0;31mCrabby\x1b[0m?':\nA \033[0;31mcrabtastic\x1b[0m game by Maia Brydon, Ela Gulsen, Shafali Gupta, and Michelle Tang!\n");
  printf("\n\nCurrently \033[0;31mwaiting for players.\x1b[0m Be patient!\n");
  
  read(server_socket, buffer, sizeof(buffer));
  //  crab_deck[size++] = 1;
  //  char * cards = calloc(250, sizeof(char));
  //  strcpy(cards, buffer);
  //  int i;
  //  for (i = 0; i < 4; i++) {
  //    char * tmp = strsep(&cards, "-");
  //    crab_deck[size++] = atoi(tmp);
  // }
  int my_player = 0;
  //the game has started bc it read.
  while (1) {

    printf("It is not your turn yet.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      // if (strcmp(buffer, ACK)) {
      // printf("received: [%s]\n", buffer);
      if (strcmp(buffer, ACK)) {
        printf("You are player \033[0;31m#%d\x1b[0m!\n", atoi(buffer));
        // printf("atoi(buffer)%d\n", atoi(buffer) );
        if(atoi(buffer) < 2) {
          printf("You are on TEAM \033[0;31m#0\x1b[0m!\n");
          printf("Your secret message is %s\n", random_m(atoi(buffer)));
        }
        else{
          printf("You are on TEAM \033[0;31m#1\x1b[0m!\n");
          printf("Your secret message is %s\n", random_m(atoi(buffer)));
        }
        printf("What would you like your \033[0;31musername\x1b[0m to be? ");
        char * response = malloc(256);
        // sscanf("%s",response);
        fgets(response,sizeof(response),stdin);

        my_player = create_player(response);
        printf("Welcome %s \n", response);
        //  printf("It is currently your turn. Here is your hand: \n\n");
        // make_hand( my_player);
        //print_hand(my_player);
        //print_table();

        for (int i =0; i< atoi(buffer); i++){
            make_hand( atoi(buffer));
        }
        
        print_hand( atoi(buffer));
        
        printf("NEED TO PRINT OUT HAND AND TABLE HERE\n");
      }
      // }
      else break;
    }
    fflush(stdin);
    fflush(stdout);
    while(check_buffer(buffer, size, crab_deck)){
      printf("PRINT OUR YOUR HAND HERE TOO \n" );
      printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
    }
    // WSJLFKDSJAKLFDJLFKJ
    // while (read(server_socket, buffer, sizeof(buffer))) {
    //   if (strcmp(buffer, ACK)) {
    //     printf("You are player \033[0;31m#%d\x1b[0m!\n", atoi(buffer));
    //     // printf("atoi(buffer)%d\n", atoi(buffer) );
    //     if(atoi(buffer) < 2) {
    //       printf("You are on TEAM \033[0;31m#0\x1b[0m!\n");
    //       printf("Your secret message is %s\n", random_m(atoi(buffer)));
    //     }
    //     else{
    //       printf("You are on TEAM \033[0;31m#1\x1b[0m!\n");
    //       printf("Your secret message is %s\n", random_m(atoi(buffer)));
    //     }
    //     printf("What would you like your \033[0;31musername\x1b[0m to be? ");
    //     char * response = malloc(256);
    //     scanf("%s",response);
    //     my_player = create_player(response);
    //
    //
    //     printf("Welcome, crab! Here are your teammates.\n\n");
    //     //  printf("It is currently your turn. Here is your hand: \n\n");
    //     // make_hand( my_player);
    //     print_hand( my_player);
    //     print_table();
    //     // printf("\n");
    //   }
    //   else break;
    // }
    // fflush(stdout);
    // fflush(stdin);
    //
    // while(check_buffer(buffer, size, crab_deck)){
    //   // fflush(stdout);
    //   printf("enter data: ");
    //   fgets(buffer, sizeof(buffer), stdin);
    //   *strchr(buffer, '\n') = 0;
    // }
    //AKDLFJSDLKJFLKJLKFKL
    // printf("What would you like your \033[0;31musername\x1b[0m to be? ");
    // char * response = malloc(256);
    // scanf("%s",response);
    // int my_player = create_player(response);

    //while the player didn't say they wanted to end their turn
    //	printf("check");


    // while(check_buffer(buffer, size, crab_deck)){
    //   printf("Would you like to switch any cards? [y/n] ");
    //   int * switch_res = malloc(256);
    //   scanf("%s",switch_res);
    //
    //   if (switch_res[0] == 'y'){
    //     printf("which cards would you like to switch? Type the card number from your hand: ");
    //     int * hand_res= malloc(256);
    //     //fgets(hand_res, 200, stdin);
    //     scanf("%d",hand_res);
    //     printf("Type the card number from the deck: ");
    //     int * deck_res = malloc(256);
    //     scanf("%d",deck_res);
    //
    //     swap_cards(atoi(buffer), *hand_res, *deck_res);
    //     //*strchr(buffer, '\n') = 0;
    //   }
    // }

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
