/*
 *Description: Unit test for scoreFor().
 *The test calculate scores for two players. The first player has some specific set of cards all putting into discard pile. The second players has the initial cards.
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

//set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int count = 0;
	int i;
	int seed = 1000;
	int numPlayer = 3;
	int p, r;
	int k[10] = {adventurer, great_hall, feast, gardens, mine, remodel, smithy, village, tribute, embargo};
	struct gameState G;
	int estateCount, duchyCount, provinceCount, greathallCount, gardenCount, curseCount; //count for scores
	int test_s;//test result value
	int result;
	int total_cards;
	bool pass = true;
	memset(&G, 23, sizeof(struct gameState));//clear the game state
	r = initializeGame(numPlayer, k, seed, &G);//initialize a new game
	//	printf("deckCount: %d\n", G.deckCount[p]);
	// player 0;
	p = 0;
#if (NOISY_TEST == 1)
	printf("\n--------TESTING scoreFor():--------\n");
	printf("\nTest 1 - Player %d:\n", p);
	printf("Putting following cards into discard pile:\n");
	printf("    4 duchy\n");
	printf("    5 provinces\n");
	printf("    3 great halls\n");
	printf("    2 gardens\n");
	printf("    1 curses\n");	
#endif
	estateCount = 3; //3 from initialization

	duchyCount = 4;//duchy
	for (i = 0; i < duchyCount; i++){
		G.discard[p][G.discardCount[p]] = duchy;
		G.discardCount[p]++;
	}

	provinceCount = 5;//province
	for (i = 0; i < provinceCount; i++){
		G.discard[p][G.discardCount[p]] = province;
		G.discardCount[p]++;
	}

	greathallCount = 3;//great_hall
	for (i = 0; i < greathallCount; i++){
		G.discard[p][G.discardCount[p]] = great_hall;
		G.discardCount[p]++;
	}

	gardenCount = 2;//gardens
	for (i = 0; i < gardenCount; i++){
		G.discard[p][G.discardCount[p]] = gardens;
		G.discardCount[p]++;
	}

	curseCount = 1;//curse
	for (i = 0; i < curseCount; i++){
		G.discard[p][G.discardCount[p]] = curse;
		G.discardCount[p]++;
	}
	result = scoreFor(p, &G);// storing scoreFor() test in result
	test_s = 0;
	test_s = test_s + (curseCount * -1); // curse -1
	test_s = test_s + estateCount;
	test_s = test_s + (duchyCount * 3); // duchy * 3
	test_s = test_s + (provinceCount * 6); //province * 6
	test_s = test_s + greathallCount;
#if (NOISY_TEST == 1)
	printf("deckCount: %d\n", G.deckCount[p]); // print deck count
	printf("discardCount: %d\n", G.discardCount[p]); // print discard count
	printf("handCount: %d\n", G.handCount[p]); // print hand count
#endif
	total_cards = G.deckCount[p] + G.discardCount[p] + G.handCount[p];
	test_s = test_s + (total_cards / 10 * gardenCount);
#if (NOISY_TEST == 1)
	printf("Player %d score: %d, expected: %d\n", p, result, test_s); // compare actual score to expected 
#endif
	if (result != test_s)
	{
		pass = false;
		count = count + 1;
	}

	p = 1;

	result = scoreFor(p, &G);

	curseCount = 0;
	estateCount = 3;
	duchyCount = 0;
	provinceCount = 0;
	greathallCount = 0;
	gardenCount = 0;

	test_s = 0;
	test_s = test_s + (curseCount * -1); // curse -1
	test_s = test_s + estateCount;
	test_s = test_s + (duchyCount * 3); // duchy * 3
	test_s = test_s + (provinceCount * 6); //province * 6
	test_s = test_s + greathallCount;
#if (NOISY_TEST == 1)
	printf("\nTest 2 - Player %d:\n", p);
	printf("All cards in deck, no additional card changes:\n");
	printf("deckCount: %d\n", G.deckCount[p]);
	printf("discardCount: %d\n", G.discardCount[p]);
	printf("handCount: %d\n", G.handCount[p]);
#endif
	total_cards = G.deckCount[p] + G.discardCount[p] + G.handCount[p];
	test_s = test_s + (total_cards / 10 * gardenCount);	
#if (NOISY_TEST == 1)
	printf("Player %d score: %d, expected: %d\n", p, result, test_s);
#endif
	if(result != test_s){
		pass = false;
		count = count + 1;
	}
	if (pass){
		printf("\nAll tests passed!\n");
	}
	else{
		printf("\n%d test(s) failed!\n", count);
	}

	return 0;
}
