/*
 *Description: unit test for council room card
 *
 *Test1: test if the supply is unchanged
 *Test2: test if deck count decrease properly
 *Test3: test if hand count increase by 3 for the first player
 *Test4: test if other players’ hand count increase by one
 *Test5: test if other players’ deck count increase by one
 *Test6: test if the number of buys increase by 1
 *Test7: test if the number of action is one less than that before using council_room.
 *
 */
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

#define NOISY_TEST 1
#define TESTCARD "Council Room"
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
	printf("--------Testing Council Room Card:-------- \n");


	printf("Verifying base state of game: \n");
	printf("Starting EState cards:   %d, expected: 12\n", G.supplyCount[1]);
	printf("Starting Duchy cards:    %d, expected: 12\n", G.supplyCount[2]);
	printf("Starting Province cards: %d, expected: 12\n", G.supplyCount[3]);



	for(i = 0; i < numPlayers; i++)
	{
		printf("Player %d\n", i);
		printf("Starting coins:        %d\n", G.coins);
		printf("Starting deckCount:    %d\n", G.deckCount[i]);
		printf("Starting handCount:    %d\n", G.handCount[i]);
		printf("Starting discardCount: %d\n\n", G.discardCount[i]);

	}
#endif
	//Test1: make sure no supply card is changed
	printf("TEST#1: Test that the supply is unchanged\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	for(i = 0; i < 25; i++)
	{

		if (test.supplyCount[i] != G.supplyCount[i])
		{
#if (NOISY_TEST)
			printf("ERROR: Expected supplyCount was: %d Actual value: %d\n", G.supplyCount[i], test.supplyCount[i]);
#endif
			fail = 1;
		}
	}
	result(fail, 1);

	//Test 2: deck count decrease properly for the first player
	printf("TEST#2: test if deck count decrease properly\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.deckCount[0] != G.deckCount[0]-4)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value:  %d  Actual Value: %d\n", G.deckCount[0] - 4, test.deckCount[0]);
#endif
		fail = 1;
	}
	result(fail, 2);

	//Test 3: hand count increase by 3 for the first player
	printf("TEST#2: test if hand count increase by 3 for the first player\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.handCount[0] != G.handCount[0]+3)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value:  %d  Actual Value: %d\n", G.deckCount[0] + 3 , test.deckCount[0]);
#endif
		fail = 1;
	}
	result(fail, 3);

	//Test 4: other players' hand count increase by one
	printf("TEST#4: test if other players' hand count increase by one.\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	for (i=1; i<numPlayers; i++)
	{
		if(test.handCount[i] != G.handCount[i]+1)
		{
#if (NOISY_TEST)
			printf("ERROR: Player %d's handcount: Expected Value:  %d  Actual Value: %d\n", i, G.handCount+1 , test.handCount[0]);

#endif
			fail = 1;
		}
	}
	result(fail, 4);

	//Test 5: other players' deck count decrease by one
	printf("TEST#5: test if other players' deck count increase by one.\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	for (i=1; i<numPlayers; i++)
	{
		if(test.deckCount[i] != G.deckCount[i]-1)
		{
#if (NOISY_TEST)
			printf("ERROR: Player %d's deckcount: Expected Value:  %d  Actual Value: %d\n", i, G.deckCount-1 , test.deckCount[0]);

#endif
			fail = 1;
		}
	}
	result(fail, 5);

	//Test 6: the number of buys increase by 1
	printf("TEST#6: test if the number of buys increase by 1\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.numBuys != G.numBuys+1)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d  Actual Value: %d\n", G.numBuys+1, test.numBuys);
#endif
		fail = 1;
	}
	result(fail, 6);

	//Test 7: the number of actions should be zero
	printf("TEST#7: test if the number of action is one less than that before using council_room\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(council_room, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.numActions != G.numActions-1)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d  Actual Value: %d\n", G.numActions-1, test.numActions);
#endif
	}
	result(fail, 7);
	
	return 0;
}
