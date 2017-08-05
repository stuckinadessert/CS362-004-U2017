/*
 *Description: unit test for adventurer card
 *Test1: test if the supply is unchanged
 *Test2: test if Hand count increase by 1
 *Test3: test if the supply is unchanged
 *Test4: test if other revealed cards are discarded
 *Test5: test if two treasure cards are added to player’s hand
 *Test6: Make sure other players are not effected
 *
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

//#define DEBUG 0
#define NOISY_TEST 1
#define TESTCARD "Adventurer"
void result(int fail, int test)
{
	if (fail == 1)
		printf("Test %d failed.\n", test);
	else
		printf("Test %d passed.\n", test); 
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
	printf("--------Testing Adventurer Card:-------- \n");
#endif

#if (NOISY_TEST)
	printf("Verifying base state of game: \n");
	printf("Starting EState cards:   %d, expected: 12\n", G.supplyCount[1]);
	printf("Starting Duchy cards:    %d, expected: 12\n", G.supplyCount[2]);
	printf("Starting Province cards: %d, expected: 12\n", G.supplyCount[3]);
#endif


	for(i = 0; i < numPlayers; i++)
	{
		printf("Player %d\n", i);
		printf("Starting coins:        %d\n", G.coins);
		printf("Starting deckCount:    %d\n", G.deckCount[i]);
		printf("Starting handCount:    %d\n", G.handCount[i]);
		printf("Starting discardCount: %d\n\n", G.discardCount[i]);

	}

	//Test 1: make sure no supply card is changed;
	printf("TEST#1: Test that the supply is unchanged\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	for(i = 0; i < 25; i++)
	{

		if (test.supplyCount[i] != G.supplyCount[i])
		{
#if (NOISY_TEST)
			printf("ERROR: Expected supplyCount was: %d Actual value: %d\n", test.supplyCount[i], G.supplyCount[i]);
#endif
			fail=1;
		}
	}
	result(fail, 1);

	//Test2: Hand count increase by 1;
	printf("TEST#2: Hand count increase by 1\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.handCount[0] != G.handCount[0] + 1)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d  Actual Value: %d\n", G.handCount[0] + 1, test.handCount[0]);
#endif
		fail = 1;
	}
	result(fail, 2);

	//Test 3: deck count decrease properly
	printf("TEST#3: Test that the supply is unchanged\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	if(test.deckCount[0] > G.deckCount[0]-2)
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: less than  %d  Actual Value: %d\n", G.deckCount[0] - 2, test.deckCount[0]);
#endif
		fail = 1;
	}
	result(fail, 3);

	//Test 4: two treasure are added to player's hand
	printf("TEST#4: Two treasure cards are added to player's hand\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	if((test.hand[0][test.handCount[0] - 1] == copper||test.hand[0][test.handCount[0] - 1] == silver || test.hand[0][test.handCount[0] - 1] == gold) &&(test.hand[0][test.handCount[0] - 2] == copper || test.hand[0][test.handCount[0] - 2] == silver || test.hand[0][test.handCount[0] - 2] == gold))
	{
#if (NOISY_TEST)
		printf("The 2 treasure cards: %d, %d\n", test.hand[0][test.handCount[0] - 1], 
				test.hand[0][test.handCount[0] - 2]);
#endif
	}
	else
	{
		fail = 1;
	}
	result(fail, 4);

	//Test 5: Other revealled cards are discarded
	printf("TEST#5: Test whether Other revealled cards are discarded\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	if((test.deckCount[0] + test.discardCount[0]) != (G.deckCount[0] + G.discardCount[0] - 2))
	{
#if (NOISY_TEST)
		printf("ERROR: Expected Value: %d Actual Value: %d\n", test.deckCount[0] + test.discardCount[0], G.deckCount[0] + G.discardCount[0] - 2);
#endif
		fail = 1;
	}
	result(fail, 5);

	//Test 6: Make sure other players are not effected
	printf("TEST#6: Make sure other players are not effected\n");
	fail = 0;
	memcpy(&test, &G, sizeof(struct gameState));
	cardEffect(adventurer, choice1, choice2, choice3, &test, handpos, &bonus);
	for(i=1; i<numPlayers; i++)
	{
		if(test.handCount[i] != G.handCount[i])
		{
#if (NOISY_TEST)
			printf("Expected handcount was: %d Actual value: %d\n", G.handCount[i], test.handCount[i]);
#endif
			fail = 1;
		}
		if(test.deckCount[i] != G.deckCount[i])
		{
#if (NOISY_TEST)
			printf("Expected deckCount was: %d Actual value: %d\n", G.deckCount[i], test.deckCount[i]);
#endif
			fail=1;
		}

	}
	result(fail, 6);

	printf("All tests complete!!\n");

	return 0;
}
