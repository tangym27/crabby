// 149.89.150.1(computer number only two digits)
#include <stdlib.h>
#include <stdio.h>
#include "networking.h"
#include "deck.h"

void process(char *s);
void subserver(int from_client);


char * team0_secret = "";
char * team1_secret = "";

int main(int argc, char **argv) {

  // char * team0_secret = random_selection(0);
  // char * team1_secret = random_selection(1);
  printf("\e[1;1H\e[2J\n\n");
  printf("Welcome to 'Why So \033[0;31mCrabby\x1b[0m?':\nA \033[0;31mcrabtastic\x1b[0m game by Maia Brydon, Ela Gulsen, Shafali Gupta, and Michelle Tang!\n");
  printf("\n\nCurrently \033[0;31mwaiting for players.\x1b[0m Be patient!\n");
  int i = 0;
  int num_players = 0;
  int listen_socket;
  int client_socket;
  int f;
  int j;
  int subserver_count = 0;
  char buffer[BUFFER_SIZE];
  char message[BUFFER_SIZE];
  char response[BUFFER_SIZE];
  char status[BUFFER_SIZE];
  char team[BUFFER_SIZE];

  int aCRABS = 0;
  int bCRABS = 0;
  int cCRABS = 0;
  int dCRABS = 0;


  if (argc < 2) {
    printf("Please enter ./server 4 \n");
    exit(1);
  }
  else {
    sscanf(argv[1], "%d", &num_players);
  }
  //set of file descriptors to read from
  // fd_set read_fds;
  int players[num_players], subservers[num_players], turns[num_players];
  listen_socket = server_setup();
  while (i < num_players) {
    players[i] = server_connect(listen_socket);
    printf("\nA new player has joined!\n");
    turns[i] = 0;
    subservers[i] = fork();
    if (!subservers[i]) {
      close(players[i]);
      return 0;
    }
    i++;
  }
  shutdown(listen_socket, SHUT_RD);
  printf("\n\nGame is starting! The action will take place in the clients' side. Buckle up!\n");
  //  char buffer[BUFFER_SIZE];


  for (i = 0; i < num_players; i++) {
    //  fflush(stdo);
    snprintf(buffer, sizeof(buffer), "%d-%d-%d-%d", 1,1,1,1);
    write(players[i], buffer, sizeof(buffer));
    snprintf(buffer, sizeof(buffer), "%d", i);
    write(players[i], buffer, sizeof(buffer));
    memset(buffer, 0, BUFFER_SIZE);
  }


  memset(buffer, 0, BUFFER_SIZE);
////// THIS DID NOT WORK YET.
// char * secret_0 = random_selection(1);
// char * secret_1 = random_selection(2);
//
// write(players[0], secret_0, sizeof(secret_0));
// write(players[1], secret_0, sizeof(secret_0));
// write(players[2], secret_1, sizeof(secret_1));
// write(players[3], secret_1, sizeof(secret_1));

  while(1) {
    for (i = 0; i < num_players; i++) {
      turns[i] += 1;
      while (turns[i]) {

        write(players[i], ACK, sizeof(ACK));
        read(players[i], buffer, sizeof(buffer));
        /*if the player wants to end their turn */
        if(strcmp(buffer, "end") == 0) {
          // strcpy(card, "this is suppose to be a card");
          read(players[i], message, sizeof(message));
          printf("message?%s\n",message );
          //printf("%s\n", card);
          //printf("cardid:%s\n", card_id);

          //strcat("Player #%d says: ", message)
          sprintf(buffer, "Player #%d says %s",i, message);
          turns[i] -= 1;
// THIS DOES NOT WORK : SERVER SIDE OF THE CHECKING CRABS FUNCTION
          // read(players[i], status, sizeof(status));
          // if (strcmp(status, "1") == 0){
          //   if (i == 0 ){
          //     aCRABS=1;
          //   }
          //   if (i == 1 ){
          //     bCRABS=1;
          //   }
          //   if (i == 2 ){
          //     cCRABS=1;
          //   }
          //   if (i == 3 ){
          //     dCRABS=1;
          //   }
          // }

        }
        else if (strcmp(buffer, "crab") == 0) {
          read (players[i], team, sizeof(team));
          if (strcmp(team, "0") == 0) {
            if (aCRABS || bCRABS){
              strcpy(response, "yes");
              write(players[i], response, sizeof(response));
            }
            else{
              strcpy(response, "no");
              write(players[i], response, sizeof(response));
            }
          }
          else if (strcmp(team, "1") == 0) {
            if (cCRABS || dCRABS){
              strcpy(response, "yes");
              write(players[i], response, sizeof(response));
            }
            else{
              strcpy(response, "no");
              write(players[i], response, sizeof(response));
            }
          }
        }


        // printf( "what%s", print_table());
    //    strcpy( buffer, return_table());
        for (j = 0; j < num_players; j++)
          if (j != i){
            write(players[j], buffer, sizeof(buffer));
          }
        // printf("here! %s a\n", buffer );
        // sprintf(buffer, "Player %d ended their turn. They sent the message '%s'", i, "dud");
        // write(players[i], "hi", 100);
        // sprintf(buffer, "Player %d ended their turn. They sent the message '%s'", i, "dud");
        // // write(client_socket, "jlkadsf", 10000);
        // printf("sdklfjs\n" );
        // if(strcmp(buffer, "end") == 0) {
        //   printf("player ended their turn!\n" );
        //   print_table();
        //   read(players[i], message, sizeof(message));
        //   if (i == 0){
        //     write(players[1], message, sizeof(message));
        //     write(players[2], message, sizeof(message));
        //     write(players[3], message, sizeof(message));
        //   }
        //   if (i == 1){
        //     write(players[0], message, sizeof(message));
        //     write(players[2], message, sizeof(message));
        //     write(players[3], message, sizeof(message));
        //   }


        }

      }
    }
  }




void subserver(int client_socket) {
  char buffer[BUFFER_SIZE];

  //for testing client select statement
  strncpy(buffer, "hello client", sizeof(buffer));
  write(client_socket, buffer, sizeof(buffer));

  while (read(client_socket, buffer, sizeof(buffer))) {
    printf("[subserver %d] received: [%s]\n", getpid(), buffer);
    process(buffer);
  //  write(client_socket, buffer, sizeof(buffer));
  }//end read loop
  close(client_socket);
  exit(0);
}

void process(char * s) {
  while (*s) {
    if (*s >= 'a' && *s <= 'z')
    *s = ((*s - 'a') + 13) % 26 + 'a';
    else  if (*s >= 'A' && *s <= 'Z')
    *s = ((*s - 'a') + 13) % 26 + 'a';
    s++;
  }
}
