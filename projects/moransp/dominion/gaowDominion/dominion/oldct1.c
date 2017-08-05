/*cardtest2.c
 * Description: Unit test for the smithy card in dominion.c
 * Smithy lets the player draw three cards.
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>
//#define DeBUG 0
#define NOISY_TEST 1
#define TESTCARD "Smithy"
int main()
{
	int i,r;
	int bonus = 0;
	int fail = 0;//indicator
	int handpos = 0;
	int choice1 = 0;
	int choice2 = 0;
	int choice3 = 0;
	int seed = 1000;
	int numPlayers = 3;
	int newcards = 3;

	struct gameState G;
	struct gameState test;
	memset(&G, 23, sizeof(struct gameState));
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};

	//initailizae a base game state
	r = initializeGame(numPlayers, k, seed, &G);

#if (NOISY_TEST)
	printf("--------Testing Smithy Card:-------- \n");
#endif

#if (NOISY_TEST)
	printf("Verifying base state of game: \n");
	printf("Starting EState cards:   %d, expected: 8\n", G.supplyCount[1]);
	printf("Starting Duchy cards:    %d, expected: 8\n", G.supplyCount[2]);
	printf("Starting Province cards: %d, expected: 8\n", G.supplyCount[3]);
#endif


	for(i = 0; i < numPlayers; i++)
	{
		printf("Player %d\n", i);
		printf("Starting coins:        %d\n", G.coins);
		printf("Starting deckCount:    %d\n", G.deckCount[i]);
		printf("Starting handCount:    %d\n", G.handCount[i]);
		printf("Starting discardCount: %d\n\n", G.discardCount[i]);

	}

	printf("Test#1: +3 cards\n");

	memcpy(&test, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(smithy, choice1, choice2, choice3, &test, handpos, &bonus);


	for (i=0; i < numPlayers; i++)
	{
#if (NOISY_TEST)
		printf("Player %d\n", i);
		printf("Test_state hand count =    %d, Base_state hand count =    %d\n", test.handCount[i], G.handCount[i]);
		printf("Test_state deck count =    %d, Base_state deck count =    %d\n", test.deckCount[i], G.deckCount[i]);
		printf("Test_state discard count = %d, Base_state discard count = %d\n", test.discardCount[i], G.discardCount[i]);
#endif
		if(i==0)
		{
			if(test.handCount[i] != G.handCount[i] + 3)
			{
#if (NOISY_TEST)
				printf("ERROR: Hand counts didn't increase properly\n");
#endif
				fail = 1;
			}
			if(test.deckCount[i] != G.deckCount[i] - 3)
			{
#if (NOISY_TEST)
				printf("ERROR: Deck counts didn't decrease properly\n");
#endif
				fail = 1;
			}
			if(test.discardCount[i] != G.discardCount[i])
			{
#if (NOISY_TEST)
				printf("ERROR: discard counts don't match\n");
#endif
				fail = 1;
			}
		}
		else
		{

			if(test.deckCount[i] != G.deckCount[i])
			{
#if (NOISY_TEST)
				printf("ERROR: Deck counts don't match\n");
#endif
				fail = 1;
			}
			if(test.handCount[i] != G.handCount[i])
			{
#if (NOISY_TEST)
				printf("ERROR: Hand counts don't match\n");
#endif
				fail = 1;
			}


			if(test.discardCount[i] != G.discardCount[i])
			{
#if (NOISY_TEST)
				printf("ERROR: discard counts don't match\n");
#endif
				fail = 1;
			}

		}	
	}
	if (fail == 1)
	{
		printf("Test#1 failed\n");
	}
	else 
		printf("Test#1 passed.\n\n");

	fail = 0;
	printf("TEST#2: Discard Smithy card\n\n");
	memcpy(&test, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(smithy, choice1, choice2, choice3, &test, handpos, &bonus);
	int j;
	for(j = 0; j < test.handCount[0]; j++)
	{
		if(test.hand[0][j] == smithy)
		{
#if (NOISY_TEST)
			printf("ERROR: Smithy is not discarded.\n");
#endif

			fail = 1;
		}
	}
	if (fail == 1)
	{
		printf("Test#2 failed\n");
	}
	else
		printf("Test#2 passed.\n\n");	

	fail = 0;
	printf("TEST#3: unchanged supply cards\n");
	memcpy(&test, &G, sizeof(struct gameState));
	choice1 = 1;
	cardEffect(smithy, choice1, choice2, choice3, &test, handpos, &bonus);
	int m;
	for(m = 0; m < 25; m++)
	{
		if(test.supplyCount[m] != G.supplyCount[m])
		{
#if (NOISY_TEST)
			printf("ERROR: Supply counts changed by Smithy cardEffect.\n");
#endif

			fail = 1;
		}
	}
	if (fail == 1) {
		printf("Test 3 failed.\n");
	} else {
		printf("Test 3 passed.\n");
	}
	printf("All tests complete!!\n");
		return 0;

}
