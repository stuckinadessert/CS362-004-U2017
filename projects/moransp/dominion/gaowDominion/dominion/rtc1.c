/*Description: random test for smithy card implementation
 *Test1: test if hand count increase properly
 *Test2: test if the card count in both deck and discard piles change properly
 *Test3: test if it discards Smithy card
 *Test4: test if it keeps supply cards unchanged.
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
	struct gameState g; //not used
	struct gameState t; //used for test
	int numTests = 1000;//iterations for testing
	int test1_pass = 0;
	int test1_fail = 0;
	int test2_pass = 0;
	int test2_fail = 0;
	int test3_pass = 0;
	int test3_fail = 0;
	int test4_pass = 0;
        int test4_fail = 0;
#if (NOISY_TEST == 1)
	printf("----------Test for playSmithy()--------\n");
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
			//fill in deck, discard, and hand with random cards
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
			int smithyCount = 0;
			for (j = 0; j < g.handCount[player]; j++)
			{
				if (g. hand[player][j] == smithy)
				{
					handPos = j;
					smithyCount = 1;
					break;
				}
			}
			if (smithyCount == 0)
			{
				handPos = floor(Random() * g.handCount[player]);
				g.hand[player][handPos] = smithy;
			}
		}
		player = rand() % numPlayer;//choose a random player
		memcpy(&t, &g, sizeof(struct gameState));
		playSmithy(&t, player, handPos);

		//test1: test if hand count increase properly
		int fail = 0;
		if (t.handCount[player] != g.handCount[player] + 2)
                                fail = 1;
		if (fail == 1)
                {
                        test1_fail++;
#if (NOISY_TEST == 1)
                        printf("Iteration #%d: Testing player #%d if hand count increase properly failed\n", i, player);
                                printf("Expected value: %d, actual value: %d\n\n", g.handCount[player] + 2, t.handCount[player]);
#endif
                }
                else
                {
                        test1_pass++;

                }
		//test2: test if the card count in both deck and discard piles change properly
		fail = 0;
		if((t.deckCount[player] + t.discardCount[player]) != (g.deckCount[player] + g.discardCount[player]) - 2)
		{
			fail = 1;
		}
		if (fail == 1)
                {
                        test2_fail++;
#if (NOISY_TEST == 1)
                        printf("Iteration #%d: Testing player #%d if the card count in both deck and discard piles change properly failed\n", i, player);
			printf("Expected value: %d, actual value: %d\n\n", g.deckCount[player] + g.discardCount[player] - 2, t.deckCount[player] + t.discardCount[player]);
#endif
		}
		else
			test2_fail++;

		//Test3: test if it discards Smithy card
		fail = 0;
		if(g.deckCount[player] >= 3)
		{
			if(t.discard[player][t.discardCount[player]-1] != smithy)
			{
				fail = 1;
			}
			if (fail == 1)
			{
				test3_fail++;
#if (NOISY_TEST == 1)
                        printf("Iteration #%d: Testing player #%d if it discards Smithy card failed\n\n", i, player);
#endif
			}
			else
				test3_pass++;
		}
		
		//Test4: test if it keeps supply cards unchanged.
		fail = 0;
		for(j = 0; j < 25; j++)
                {

                        if (t.supplyCount[j] != g.supplyCount[j])
                        {
                                fail = 1;
                        }
                }
                if (fail == 0)

                        test4_pass++;
                else
                {
                        test4_fail++;
#if (NOISY_TEST == 1)
                        printf("Iteration #%d: Testing player #%d whether the supply cards are unchanged failed\n\n", i, player);
#endif
                }
	}
#if (NOISY_TEST == 1)
	printf("Random testing for playSmithy() completed.\n");
        printf("=================================================\n\n");
	printf("test1: test if hand count increase properly \n");
	printf("%d out of %d tests passed!\n", test1_pass, test1_pass + test1_fail);
        printf("%d out of %d tests failed!\n\n", test1_fail, test1_pass + test1_fail);

	printf("test2: test if the card count in both deck and discard piles change properly\n");
        printf("%d out of %d tests passed!\n", test2_pass, test2_pass + test2_fail);
        printf("%d out of %d tests failed!\n\n", test2_fail, test2_pass + test2_fail);

	printf("test3: test if it discards Smithy card\n");
        printf("%d out of %d tests passed!\n", test3_pass, test3_pass + test3_fail);
        printf("%d out of %d tests failed!\n\n", test3_fail, test3_pass + test3_fail);

	printf("test4: test if it keeps supply cards unchanged\n");
        printf("%d out of %d tests passed!\n", test4_pass, test4_pass + test4_fail);
        printf("%d out of %d tests failed!\n\n", test4_fail, test4_pass + test4_fail);
#endif
	return 0;
}

