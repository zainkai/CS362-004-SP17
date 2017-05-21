#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TESTMAX 50
#define TESTCARD "outpost"

int passing_tests = 0;

/*
 REFS: betterTestDrawCard.c, cardtest1.c
*/

int main () {
    srand(time(NULL));

    int i, j, players_total,choice1,choice2,choice3,cur_player;

    int test_val_start, test_val_end,test_val_start2,test_val_end2;

    int bonus = 0,handpos = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;

    for(i=0;i < TESTMAX;i++){

        players_total = rand() % 4 + 1;
        // initialize a game state and player cards
        //initializeGame(numPlayers, k, seed, &G);
        //memset(&G,0,sizeof(G) -1);
        initializeGame(players_total, k, rand(), &G);

        cur_player = whoseTurn(&G);

        for(j = 0;j < players_total;j++){
            G.deckCount[j] = rand() % MAX_DECK +1;
            G.discardCount[j] = rand() % MAX_DECK +1;
            G.handCount[j] = rand() % MAX_HAND + 1;
        }

        choice1 = rand() % 2 + 0;
        choice2 = rand() % 2 + 0;
        choice3 = rand() % 2 + 0;

        test_val_start = G.handCount[cur_player];
        test_val_start2 = G.outpostPlayed;
        //testing effect
        cardEffect(outpost,choice1,choice2,choice3,&G,handpos,&bonus);
        test_val_end = G.handCount[cur_player];
        test_val_end2 = G.outpostPlayed;

        //great hall is discarded thus start and end values will equal.
        if(test_val_start -1 == test_val_end && test_val_start2 +1 == test_val_end2){
            passing_tests++;
        }
    }

    /***** End of testing *****/
    printf("%s tests: %d/%d passed\n",TESTCARD,passing_tests,TESTMAX);

    return 0;
}
