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


  if (argc < 2) {
    printf("Please enter ./server 4 or ./server 6\n");
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

  while(1) {
    for (i = 0; i < num_players; i++) {
      turns[i] += 1;
      while (turns[i]) {
        write(players[i], ACK, sizeof(ACK));
        read(players[i], buffer, sizeof(buffer));
        if(strcmp(buffer, "end") == 0) {

          // strcpy(card, "this is suppose to be a card");
          read(players[i], message, sizeof(message));
          printf("message?%s\n",message );
          //printf("%s\n", card);
          char card_id[8];
          sprintf(card_id, "5");
          //printf("cardid:%s\n", card_id);
          write(players[i], card_id, sizeof(card_id));


          sprintf(buffer, "%s", message);
          turns[i] -= 1;
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
        //   printf("everything is gucci\n" );
          // char card[50];
          // strcpy(card, draw_card(deck, &deck_size));
          // //printf("%s\n", card);
          // char card_id[8];
          // sprintf(card_id, "%d", get_card_id(card));
          // //printf("cardid:%s\n", card_id);
        //  sprintf(buffer, "Player %d ended their turn. They sent the message '%s'", i, "dud");

        }

      }
    }
  }



/////done

//   while (1) {
//     //select() modifies read_fds
//     //we must reset it at each iteration
//     FD_ZERO(&read_fds); //0 out fd set
//     FD_SET(STDIN_FILENO, &read_fds); //add stdin to fd set
//     FD_SET(listen_socket, &read_fds); //add socket to fd set
//
//     //select will block until either fd is ready
//     select(listen_socket + 1, &read_fds, NULL, NULL, NULL);
//
//     //if listen_socket triggered select
//     if (FD_ISSET(listen_socket, &read_fds)) {
//      client_socket = server_connect(listen_socket);
//
//      f = fork();
//      if (f == 0)
//        subserver(client_socket);
//      else {
//        subserver_count++;
//        close(client_socket);
//      }
//     }//end listen_socket select
//
//     //if stdin triggered select
//     if (FD_ISSET(STDIN_FILENO, &read_fds)) {
//       //if you don't read from stdin, it will continue to trigger select()
//       fgets(buffer, sizeof(buffer), stdin);
//       printf("[server] subserver count: %d\n", subserver_count);
//     }//end stdin select
//   }
// }

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
