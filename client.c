#include "networking.h"

int check_buffer(char * buffer, int size, int crab_deck[]){
  if (strcmp(buffer, "draw") == 0)
    return 0;
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
    while(check_buffer(buffer, size, crab_deck)){
      printf("enter data: ");
      fgets(buffer, sizeof(buffer), stdin);
      *strchr(buffer, '\n') = 0;
    }

    // write(server_socket, buffer, sizeof(buffer));
    //   memset(buffer, 0, BUFFER_SIZE);
    //   read(server_socket, buffer, sizeof(buffer));
    //   //printf("buffer:%s\n", buffer);
    //   int id = atoi(buffer);
    // //  printf("Card name: %s\n",get_card_name(catalog, id) );
    //   char * name = calloc(50, sizeof(char));
    //   name = "boop";
    //   sprintf(buffer, "Drew the %s card.\n", name);
    //   //if (strcmp(name, "Exploding Kitten")){
    //   memset(buffer, 0, BUFFER_SIZE);
    //   strcpy(buffer, "drew");
    //   write(server_socket, buffer, sizeof(buffer));
    //   crab_deck[size] = id;
    //   size++;
    //  }
  }
}
