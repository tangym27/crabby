#include "networking.h"
#include "player.h"
#include "deck.h"

#include <stdio.h>
#include <time.h>

int buff_content(char * buffer, int size){
  if (strcmp(buffer, "end") == 0){
  //  printf("(end happened)\n" );
    return 0;
  }
  return 1;
}

int main(int argc, char **argv) {
  srand(time(NULL));

  printf("\e[1;1H\e[2J\n\n");
  printf("Welcome to 'Why So \033[0;31mCrabby\x1b[0m?':\nA \033[0;31mcrabtastic\x1b[0m game by Maia Brydon, Ela Gulsen, Shafali Gupta, and Michelle Tang!\n");
  printf("\n\nCurrently \033[0;31mwaiting for players.\x1b[0m Be patient!\n");

  int size = 1000;
  int crab_deck[51];
  int server_socket;
  char buffer[BUFFER_SIZE];
  char username[100];
  char message[BUFFER_SIZE];
  char deckpos[BUFFER_SIZE];
  char handpos[BUFFER_SIZE];
  char team[BUFFER_SIZE];
  char response[BUFFER_SIZE];
  char status[BUFFER_SIZE];

  if (argc == 2) server_socket = client_setup( argv[1]);
  else server_socket = client_setup( TEST_IP );

  int my_player = 0;
  int SETUP = 1;
  int SETUP2 =1;
  //the game has started bc it read.
  while (1) {
    int ONCE = 0;
    printf("It is not your turn yet.\n");
    while (read(server_socket, buffer, sizeof(buffer))) {
      if (strcmp(buffer, ACK) && SETUP) {

        printf("What would you like your \033[0;31musername\x1b[0m to be? ");
        char * response = malloc(256);
        fgets(response,sizeof(response),stdin);
        *strchr(response, '\n') = 0;

        my_player = create_player(response);
        printf("Welcome, %s!\n", response);

        printf("In this game, you will be switching cards between your hand and the table as well as looking out\n");
        printf("For when your hand contains 4 of the same card - that's called 'crabs'.\n");

        printf("When it is your turn, you will be asked if you'd like to switch cards. Generally, if you don't have crabs, you should say yes\n");
        printf("To get a hand that has more cards of a kind. Remember, your opponent will be switching cards too, so be fast!\n");

        printf("\n\nWhen you are done switching, enter 'end' and your turn will be over. Afterwards, you will have to send a secret message.\n");
        printf("What is this secret message, you ask? Well... in a few seconds, you will receive your team's very own secret message category.\n");
        printf("This category can be something like books, foods, or people. If your hand contains crabs, send a message that fits the theme of the secret.\n");
        printf("Otherwise, try to trick your teammates into thinking you really do have crabs by sending ambiguous messages that don't fit your secret!\n");

        printf("Anyway, that was a lot of explanation. Let's go to playing the game, huh?\n\n");

        printf("NEED TO PRINT OUT HAND AND TABLE HERE\n");
        SETUP = 0;
      }
      else if (strcmp(buffer, ACK) && SETUP2) {
        printf("You are player \033[0;31m#%d\x1b[0m!\n", atoi(buffer));
        if(atoi(buffer) < 2) {
          printf("You are on TEAM \033[0;31m#0\x1b[0m!\n");
          printf("Your secret message is \033[0;31m#%s\x1b[0m!\n",  random_m(atoi(buffer)));
        }
        else{
          printf("You are on TEAM \033[0;31m#1\x1b[0m!\n");
          printf("Your secret message is \033[0;31m#%s\x1b[0m!\n", random_m(atoi(buffer)));
        }
        printf("It is currently your turn. Here is your hand: \n");
        make_deck();
        make_hand(my_player);
        print_hand(my_player);
        create_table();
        print_table();
        SETUP2=0;
      }
      else if(strcmp(buffer, ACK)){
          printf("received: [%s]\n", buffer);
      }
      else{
        break;
      }

    }
    fflush(stdin);
    fflush(stdout);
    while(buff_content(buffer, size)){
      printf("Command: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;

      if (strcmp(buffer, "swap") == 0){ //if the player wants to swap their card for one on the table
        printf("Which card do you want to put on the table? (enter card index num)\n");
        fgets(handpos, sizeof(buffer), stdin);
        *strchr(handpos, '\n') = 0;
        printf("Which card on the table do you want to take? (enter card index num)\n");
        fgets(deckpos, sizeof(buffer), stdin);
        *strchr(deckpos, '\n') = 0;
        swap_cards(my_player, atoi(handpos), atoi(deckpos));
      //  printf("atoi(handpos)%d\n", atoi(handpos) );
        print_hand(my_player);
        print_table();
      }

      if(strcmp(buffer, "new table") == 0){ //if the player wants a new table, but can only be called once per turn. 
        if (ONCE){
          printf("Sorry! You already switched it once before. Try again on your next turn!\n" );
        }
        else{
          printf("Changing table cards...\n");
          create_table();
          print_table();
          ONCE=1;
        }
      }
/////////////////////// THIS DOES NOT WORK -- YET TO BE IMPLEMENTED WITH SERVER. 
      if (strcmp(buffer, "crabs") == 0){
        printf("Which team would you like to call for having crabs (0 or 1)?\n");
        fgets(team, sizeof(buffer), stdin);
        *strchr(team, '\n') = 0;
        // ask server to check crabs
        // server response
        write(server_socket, buffer, sizeof(buffer));
        memset(buffer, 0, BUFFER_SIZE);
      //  write(server_setup, team, sizeof(team));

        read(server_socket, response, sizeof(response));
        if (strcmp(response, "yes") == 0){
          got_crabs(my_player);
        }
        else{
          not_crabs(my_player);
        }
        print_hand(my_player);
        print_table();
      }
    }
///////////////////////
    if (!strcmp(buffer, "end")){ //if playes said they wanted to end their turn
      printf("your turn has ended.\n");
      write(server_socket, buffer, sizeof(buffer));
      memset(buffer, 0, BUFFER_SIZE);

      printf("Please enter a message to send to the other users: \n");
      fgets(message, sizeof(message),stdin);
      *strchr(message, '\n') = 0;
      write(server_socket, message, sizeof(message));

      memset(buffer, 0, BUFFER_SIZE);

      read(server_socket, buffer, sizeof(buffer));
      sprintf(buffer, "send a message.\n");
    }

  }
}
