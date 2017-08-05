/*Description: random test for village card implementation
 *Test1: Test if the supply is unchanged
 *Test2: test if card count in deck and discard pile change properly
 *Test3: test if Hand count increase properly.
 *Test4: test if action increase properly.
 *Test5: test if the number of buys unchanged.
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define NOISY_TEST 1

int main()
{
	srand(time(NULL));
	int i;
	int j;
	int player;
	int numPlayer;
	int handPos;
	int seed = rand();
	int k[10] = { adventurer, council_room, feast, gardens, mine
		, remodel, smithy, village, baron, great_hall };
	struct gameState g;
	struct gameState t;
	int numTests = 1000;
	int test1_pass = 0;
	int test1_fail = 0;
	int test2_pass = 0;
	int test2_fail = 0;
	int test3_pass = 0;
	int test3_fail = 0;
	int test4_pass = 0;
	int test4_fail = 0;
	int test5_pass = 0;
	int test5_fail = 0;
#if (NOISY_TEST == 1)
	printf("----------Test for playVillage()--------\n");
#endif
	for(i = 0; i < numTests; i++)
	{
		numPlayer = (rand() % (3)) + 2;
		memset(&g, 23, sizeof(struct gameState));
		initializeGame(numPlayer, k, seed, &g);
		for(player = 0; player < numPlayer; player++)
		{
			g.deckCount[player] = floor(Random() * MAX_DECK);
			g.discardCount[player] = floor(Random() * MAX_DECK);
			g.handCount[player] = floor(Random() * MAX_HAND);
			for(j = 0; j < g.deckCount[player]; j++)
			{
				g.deck[player][j] = floor(Random() * treasure_map);
			}
			for(j = 0; j < g.discardCount[player]; j++)
			{
				g.discard[player][j] = floor(Random() * treasure_map);
			}
			for(j = 0; j < g.handCount[player]; j++)
			{
				g.hand[player][j] = floor(Random() *treasure_map);
			}
			int villageCount = 0;
			for(j = 0; j < g.handCount[player]; j++)
			{
				if (g. hand[player][j] == village)
				{
					handPos = j;
					villageCount = 1;
					break;
				}
			}
			if (villageCount == 0)
			{
				handPos = floor(Random() * g.handCount[player]);
				g.hand[player][handPos] = village;
			}
		}
		player = rand() % numPlayer;//choose a random player
		memcpy(&t, &g, sizeof(struct gameState));
		playVillage(&t, player, handPos);
		//Test1: Test if the supply is unchanged
		int fail = 0;
		for(j = 0; j < 25; j++)
		{

			if (t.supplyCount[j] != g.supplyCount[j])
			{
				fail = 1;
			}
		}
	
		if (fail == 1)
		{
			test1_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d whether the supply cards are unchanged failed\n\n", i, player);
#endif
		}
		else
			test1_pass++;


		//Test2: test if card count in deck and discard pile change properly
		fail = 0;
		if((t.deckCount[player] + t.discardCount[player]) != (g.deckCount[player] + g.discardCount[player]))
		{
			fail = 1;
		}
		if (fail == 1)
		{
			test2_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if the card count in both deck and discard piles change properly failed\n", i, player);
			printf("Expected value: %d, actual value: %d\n\n", g.deckCount[player] + g.discardCount[player], t.deckCount[player] + t.discardCount[player]);
#endif
		}
		else
			test2_pass++;
		//Test3: test if Hand count increase properly.
		fail = 0;
		if (t.handCount[player] != g.handCount[player])
			fail = 1;
		if (fail == 1)
		{
			test3_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if hand count increase properly failed\n", i, player);
			printf("Expected value: %d, actual value: %d\n\n", g.handCount[player], t.handCount[player]);
#endif
		}
		else
		{
			test3_pass++;
		}
		//Test4: test if action increase properly.
		fail = 0;
		if(t.numActions != g.numActions + 1)
			fail = 1;
		if (fail == 1)
		{
			test4_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if action increase properly failed\n", i, player);
			printf("Expected value: %d, actual value: %d\n\n", g.numActions + 1, t.numActions);
#endif
		}
		else
		{
			test4_pass++;
		}
		//Test5: test if the number of buys unchanged.
		fail = 0;
		if(t.numBuys != g.numBuys)
			fail = 1;
		if (fail == 1)
		{
			test5_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if the number of buys unchanged failed\n", i, player);
			printf("Expected value: %d, actual value: %d\n\n", g.numBuys, t.numBuys);
#endif
		}
		else
		{
			test5_pass++;
		}
	}
#if (NOISY_TEST == 1)
	printf("Random testing for playVillage() completed.\n");
	printf("=================================================\n\n");
	printf("test1: Test if the supply is unchanged\n");
	printf("%d out of %d tests passed!\n", test1_pass, test1_pass + test1_fail);
	printf("%d out of %d tests failed!\n\n", test1_fail, test1_pass + test1_fail);

	printf("test2: Test if card count in deck and discard pile change properly\n");
	printf("%d out of %d tests passed!\n", test2_pass, test2_pass + test2_fail);
	printf("%d out of %d tests failed!\n\n", test2_fail, test2_pass + test2_fail);

	printf("test3: Test if Hand count increase properly.\n");
	printf("%d out of %d tests passed!\n", test3_pass, test3_pass + test3_fail);
	printf("%d out of %d tests failed!\n\n", test3_fail, test3_pass + test3_fail);

	printf("test4: Test if action increase properly.\n");
	printf("%d out of %d tests passed!\n", test4_pass, test4_pass + test4_fail);
	printf("%d out of %d tests failed!\n\n", test4_fail, test4_pass + test4_fail);

	printf("test5: Test if the number of buys unchanged.\n");
	printf("%d out of %d tests passed!\n", test5_pass, test5_pass + test5_fail);
	printf("%d out of %d tests failed!\n\n", test5_fail, test5_pass + test5_fail);

#endif
	return 0;

}




