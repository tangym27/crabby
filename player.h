#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <errno.h>

#ifndef PLAYER_H
#define PLAYER_H

int create_player(char * usrname);
int form_team( int player_no0, int player_no1);
int make_hand( int player_no);
int add_point( int player_no);
int get_points( int player_no);
int check_crabs( int player_no);
int print_hand( int player_no);
int swap_cards( int player_no, int player_card_index, int deck_card_index);
int switch_turns( int team_no);
int called_crabs( int check_team, int caller_team);

#endif
