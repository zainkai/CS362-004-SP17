#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <time.h>

//globals for passes and fails
int passes = 0;
int fails = 0;

#define MAX_TESTS 100

void testCard(struct gameState state, int k[]){
    int  i, j, n, players, player, handCount, deckCount, seed, address;
    for(i=0;i < MAX_TESTS;i++){
		seed = rand();
		players = rand() % 4;
		initializeGame(players,k,seed,&state);

		state.deckCount[player] = rand() % MAX_DECK;
		state.discardCount[player] = rand() % MAX_DECK;
		state.handCount[player] = rand() % MAX_HAND;

		handCount = state.handCount[player];
		deckCount = state.deckCount[player];
        int choice = rand() % 2;
        int choice1 = rand() % 2;
        int choice2 = rand() % 2;
        int currentPlayer = whoseTurn(&state);
        int currentHandCount = state.handCount[currentPlayer];
		cardEffect(smithy,choice,choice1,choice2,&state,0,0);
        int afterHandCount = state.handCount[currentPlayer];
		if(afterHandCount > currentHandCount){
            //handcount must be increased
            passes++;
		}else {
            fails++;
		}

	}

}

int main(){

	printf("Testing Smithy!\n");

	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse,
	       sea_hag, tribute, smithy};
	int  i, j, n, players, player, handCount, deckCount, seed, address;
	struct gameState state1;
	struct gameState state2;
	struct gameState state3;

	testCard(state1, k);
    testCard(state2, k);
    testCard(state3, k);
    printf("Test Passed: %d, Test Failed: %d\n", passes, fails);

	return 0;
}
