#include <stdlib.h>
#include <stdio.h>
#include <time.h>

char * secrets[13] = {"Red Vegetables", "Cool-Toned Fruits", "Small Dogs", "Big Dogs", "Names of CS Teachers", "Literary Characters' Last Names", "Desserts", "Naturally Occuring Structures", "Disney Characters", "Scientists' First Names", "Stuff you can buy at Muji", "Stuff you CAN'T buy at Muji", "New York Street Names"};

char * random_selection( int team_no) {
    srand( time( NULL));
    int rand_no;
    for (int i = 0; i < team_no; i++) {
        rand_no = rand();
    }
    return secrets[ rand_no % 13];
}
