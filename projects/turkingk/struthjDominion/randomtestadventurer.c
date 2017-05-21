#include <assert.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "dominion.h"
#include "rngs.h"
#include <time.h>
#define MAX_TESTS 100

//globals for passes and fails
int passes = 0;
int fails = 0;

//helper function to count treasure cards
int countTreasureCards(int numPlayers,struct gameState *state){
    int numTreasure = 0;
	int card;
	for(int i = 0; i < numPlayers; i++) {
		for(int j = 0; j < state->handCount[i]; j++) {
			card = state->hand[i][j];
			if(card == copper || card == silver || card == gold) {
				numTreasure++;
			}
		}
	}
	return numTreasure;
}


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
        int startingTreasure = countTreasureCards(players,&state);
		cardEffect(adventurer,choice,choice1,choice2,&state,0,0);
        int endingTreasure = countTreasureCards(players,&state);
        if(endingTreasure > startingTreasure){
            //correctly added 2 treasures
            passes++;
        }else {
            //didn't add two treasures failed
            fails++;
        }
	}

}




int main(){
    printf("Testing Adventurer!\n");
      int k[10] = {adventurer, council_room, copper, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
    //test adventure
    //struct gameState* state = newGame();
    struct gameState state1, state2, state3;
    testCard(state1, k);
    //display re    printf("Test Passed: %d, Test Failed: %d\n", passes, fails);sults
    printf("Test Passed: %d, Test Failed: %d\n", passes, fails);


    return 0;
}
