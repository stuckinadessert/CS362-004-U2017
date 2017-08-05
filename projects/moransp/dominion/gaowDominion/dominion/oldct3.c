/*
 *Description: unit test for village
 *Test1: Test if the supply is unchanged
 *Test2: test if deck count decrease properly
 *Test3: test if Hand count increase by 1
 *Test4: test if action increase by 2.
 *Test5: test if the number of buys unchanged.
 */
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NOISY_TEST 1
#define TESTCARD "Village"

void result(int fail, int test)
{
	if (fail == 1)
		printf("Test %d failed.\n\n", test);
	else
		printf("Test %d passed.\n\n", test);
}

int main()
{
	int i = 0;
	int fail = 0;
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int seed = 1000;
	int bonus = 0;
	int numPlayers = 3;
	struct gameState G;
	struct gameState test;
	int k[10] = {adventurer, council_room, feast, gardens, mine,
		remodel, smithy, village, baron, great_hall};
	initializeGame(numPlayers, k, seed, &G);
#if (NOISY_TEST)
	printf("--------Testing village Card: --------\n");


	printf("Verifying base state of game: \n");
	printf("Starting EState cards:   %d, expected: 8\n", G.supplyCount[1]);
	printf("Starting Duchy cards:    %d, expected: 8\n", G.supplyCount[2]);
	printf("Starting Province cards: %d, expected: 8\n", G.supplyCount[3]);



	for(i = 0; i < numPlayers; i++)
	{
		printf("Player %d\n", i);
		printf("Starting coins:        %d\n", G.coins);
		printf("Starting deckCount:    %d\n", G.deckCount[i]);
		printf("Starting handCount:    %d\n", G.handCount[i]);
		printf("Starting discardCount: %d\n\n", G.discardCount[i]);

	}
#endif

	//Test 1: make sure no supply card is changed;
	printf("TEST#1: Test that the supply is unchanged\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &test, handpos, &bonus);
	for(i = 0; i < 25; i++)
	{

		if (test.supplyCount[i] != G.supplyCount[i])
		{
#if (NOISY_TEST)
			printf("ERROR: Expected supplyCount was: %d Actual value: %d\n", G.supplyCount[i], test.supplyCount[i]);
#endif
			fail=1;
		}
	}
	result(fail, 1);

	//Test2: deck count decrease properly
	printf("TEST#2: test if deck count decrease properly\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.deckCount[0] != G.deckCount[0]-1)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value:  %d  Actual Value: %d\n", G.deckCount[0] - 1, test.deckCount[0]);
#endif
		fail = 1;
	}
	result(fail, 2);

	//Test3: Hand count remains the same
	printf("TEST#3: test if Hand count increase by 1\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	if(test.handCount[0] != G.handCount[0])
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d  Actual Value: %d\n", G.handCount[0], test.handCount[0]);
#endif
		fail = 1;
	}
	result(fail, 3);

	//Test4: Action increase by 2
	printf("TEST#4: test if action increase by 2.\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.numActions != G.numActions+1)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d  Actual Value: %d.\n", G.numActions+1, test.numActions);
#endif
		fail = 1;
	}
	result(fail,4);

	//Test5: buynumber remain the same
	printf("TEST#5: test if the number of buys unchanged.\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(village, choice1, choice2, choice3, &test, handpos, &bonus);	
	if(test.numBuys != G.numBuys)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d  Actual Value: %d\n", G.numBuys, test.numBuys);
#endif
		fail = 1;
	}
	result(fail,5);

	//Test6: 

	return 0;
}
















