#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define MAX_TESTS 3000

struct gameState* randSetup(int players, struct gameState* state) {
	int i;
	int player;

	for(player = 0; player < players; player++) {
		if((rand() % 5) != 0) { // 4/5 of the time we get a random deck
			state->deckCount[player] = rand() % MAX_DECK;
			for(i = 0; i < state->deckCount[player]; i++) {
				state->deck[player][i] = rand() % 27;
			}
		} else { // the other 1/5 of the time we get a deck of size 0;
			state->deckCount[player] = 0;
		}
		state->handCount[player] = rand() % MAX_HAND;
		for(i = 0; i < state->handCount[player]; i++) {
			state->hand[player][i] = rand() % 27;
		}
		state->discardCount[player] = rand() % MAX_DECK;
		for(i = 0; i < state->discardCount[player]; i++) {
			state->discard[player][i] = rand() % 27;
		}
	}
	return state;
}

int countInitTreasures(int players, struct gameState* state) {
	int initialTreasures = 0;
	int player;
	int card;
	int i;

	for(player = 0; player < players; player++) {
		for(i = 0; i < state->handCount[player]; i++) {
			card = state->hand[player][i];
			if(card == copper || card == silver || card == gold) {
				initialTreasures++;
			}
		}
	}
	return initialTreasures;
}

int countFinalTreasures(int players, struct gameState* state) {
	int finalTreasures = 0;
	int player;
	int card;
	int i;

	for(player = 0; player < players; player++) {
		for(i = 0; i < state->handCount[player]; i++) {
			card = state->hand[player][i];
			if(card == copper || card == silver || card == gold) {
				finalTreasures++;
			}
		}
	}
	return finalTreasures;
}

int main() {
	int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};

	int handPos[4] = {0, 0, 0, 0};

	int i, n, players, player, seed, finalTreasures = 0,
	successes = 0, failures = 0, initialTreasures = 0, choice1, choice2, choice3;

	struct gameState* state = newGame();
	srand(time(NULL));

	printf("Random Adventurer Test\n");

	for(i = 0; i < MAX_TESTS; i++) {
		players = (rand() % 3) + 2;
		seed = rand();
		initializeGame(players, k, 0, state);
		state = randSetup(players, state);
		choice1 = rand() % 2;
		choice2 = rand() % 2;
		choice3 = rand() % 2;
		initialTreasures = countInitTreasures(players, state);
		for(player = 0; player < players; player++) {
			handPos[player] = rand() % 4;
			n = cardEffect(adventurer, choice1, choice2, choice3, state, handPos[player], 0);
			if(n != 0) {
				failures++;
			}
		}
		finalTreasures = countFinalTreasures(players, state);
		if((finalTreasures/players) == (initialTreasures/players) + 2) {
			successes++;
		} else {
			failures++;
		}
		printf("Initial Treasures: %d\n", initialTreasures);
		printf("Final Treasures: %d\n", finalTreasures);
	}

	printf("Successes: %d\n", successes);
	printf("Failures: %d\n", failures);
	printf("End Random Adventurer Test\n");
	return 0;
}
