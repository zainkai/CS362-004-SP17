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
#define TESTCARD "adventurer"

int passing_tests = 0;

/*
 REFS: betterTestDrawCard.c, cardtest1.c
*/

int treasures_in_hand(struct gameState *G,int player){
    int treasures = 0, card_in_hand, i;

    for(i = 0; i < G->handCount[player];i++){
        card_in_hand = G->hand[player][i];

        if(card_in_hand == copper
        || card_in_hand == silver
        || card_in_hand == gold){
            treasures += 1;
        }
    }
    return treasures;
}

int main (void) {
    srand(time(NULL));

    int i, j, players_total, cur_player,choice1,choice2,choice3;

    int test_val_start, test_val_end;

    int bonus = 0,handpos = 0;

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                remodel, smithy, village, baron, great_hall};
    struct gameState G;

    for(i=0;i < TESTMAX;i++){

        players_total = rand() % 4 + 1;
        // initialize a game state and player cards
        //initializeGame(numPlayers, k, seed, &G);
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

        test_val_start = treasures_in_hand(&G,cur_player);
        //testing effect
        cardEffect(adventurer,choice1,choice2,choice3,&G,handpos,&bonus);
        test_val_end = treasures_in_hand(&G,cur_player);

        if(test_val_start + 2 == test_val_end){
            passing_tests++;
        }
    }

    /***** End of testing *****/
    printf("%s tests: %d/%d passed\n",TESTCARD,passing_tests,TESTMAX);

    return 0;
}
