/*Description: random test for adventurer card implementation
 *test1: make sure no supply card is changed;
 *test2: test if hand count increase properly
 *test3: test if deck count decrease properly
 *test4: treasure cards are added to player's hand
 *test5: Other revealled cards are discarded
 *
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
	int test5_pass = 0;
	int test5_fail = 0;
#if (NOISY_TEST == 1)
	printf("----------Test for playAdventurer()--------\n");
#endif
	for(i = 0; i < numTests; i++)
	{
		numPlayer = (rand() % (3)) + 2; // random amount of players 2-4
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
			int adventurerCount = 0;
			for (j = 0; j < g.handCount[player]; j++)
			{
				if (g. hand[player][j] == adventurer)
				{
					adventurerCount = 1;
					break;
				}
			}
			if (adventurerCount == 0)
			{
				handPos = floor(Random() * g.handCount[player]);
				g.hand[player][handPos] = adventurer;
			}
		}
		player  = rand() % numPlayer; //choose a random player
		memcpy(&t, &g, sizeof(struct gameState));
		playAdventurer(player, &t);

		//test1: make sure no supply card is changed;
		int fail = 0;
		for(j = 0; j < 25; j++)
		{

			if (t.supplyCount[j] != g.supplyCount[j])
			{
				fail = 1;
			}
		}
		if (fail == 0)

			test1_pass++;
		else
		{
			test1_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d whether the supply cards are unchanged failed\n\n", i, player);
#endif
		}
		int num_treasure = 0;
		int deckpos;
		int card_t;
		for(j = 0; j < g.deckCount[player]; j++)
		{
			card_t = g.deck[player][j];
			if (card_t == copper || card_t == silver || card_t == gold)
			{
				if (num_treasure == 0)
				{	
					deckpos = j;
				}
				num_treasure++;

			}
		}

		//test2: test if hand count increase properly
		fail = 0;
		if (num_treasure == 0)
		{
			if (t.handCount[player] != g.handCount[player] - 1)
				fail = 1;
		}
		if (num_treasure == 1)
		{
			if (t.handCount[player] != g.handCount[player])
				fail = 1;
		}
		if (num_treasure >= 2)
		{
			if (t.handCount[player] != g.handCount[player] + 1)
				fail = 1;
		}
		if (fail == 1)
		{
			test2_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if hand count increase properly failed\n", i, player);
			if (num_treasure == 0)
			{

				printf("Expected value: %d, actual value: %d\n\n", g.handCount[player] - 1, t.handCount[player]);
			}
			if (num_treasure == 1)
			{
				printf("Expected value: %d, actual value: %d\n\n", g.handCount[player], t.handCount[player]);
			}
			if (num_treasure >= 2)
			{
				printf("Expected value: %d, actual value: %d\n\n", g.handCount[player] + 1, t.handCount[player]);
			}
#endif			
		}
		else
		{
			test2_pass++;

		}
		//test3: test if deck count decrease properly
		fail = 0;
		if (num_treasure == 1 || 2)
		{
			if(t.deckCount[player] != deckpos)
				fail = 1;
		}
		if (num_treasure > 2)
		{
			if (g.deckCount[player] >= t.deckCount[player] + 2) 
				fail = 1;
		}
		if (fail == 1)
		{
			test3_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if deck count decrease properly failed\n", i, player);
			if (num_treasure == 1||2)
			{
				printf("Expected value: %d, actual value: %d\n\n", deckpos, t.deckCount[player]);
			}
			if (num_treasure > 2)
			{
				printf("Expected value: %d, actual value: %d\n\n", g.deckCount[player], t.deckCount[player]+2);
			}
#endif			
		}
		else
			test3_pass++;
		//Test 4: treasure cards are added to player's hand
		fail = 0;
		int g_treasureNum = 0;
		int t_treasureNum = 0;
		for (j = 0; j < g.handCount[player]; j++)
		{
			card_t = g.hand[player][j];
			if (card_t == copper || card_t == silver || card_t == gold)
			{
				g_treasureNum++;
			}
		}
		for (j = 0; j < t.handCount[player]; j++)
		{
			card_t = t.hand[player][j];
			if (card_t == copper || card_t == silver || card_t == gold)
			{
				t_treasureNum++;
			}
		}
		if (num_treasure == 0)
		{
			if(g_treasureNum != t_treasureNum)
			{
				fail = 1;
			}		
		}
		if (num_treasure == 1)
		{
			if(g_treasureNum != t_treasureNum - 1)
			{
				fail = 1;
			}  
		}
		if (num_treasure >= 2)
		{
			if(g_treasureNum != t_treasureNum - 2)
			{
				fail = 1;
			}
		}
		if (fail == 1)
		{
			test4_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if treasure cards are added to player's hand failed\n", i, player);
			if (num_treasure == 0)
			{

				printf("Expected value: %d, actual value: %d\n\n", g_treasureNum, t_treasureNum);
			}
			if (num_treasure == 1)
			{
				printf("Expected value: %d, actual value: %d\n\n", g_treasureNum, t_treasureNum - 1);
			}
			if (num_treasure >= 2)
			{
				printf("Expected value: %d, actual value: %d\n\n", g_treasureNum, t_treasureNum - 2);
			}
#endif			
		}
		else
			test4_pass++;

		//Test 5: Other revealled cards are discarded
		fail = 0;
		if (num_treasure == 0)
		{
			if((t.deckCount[player] + t.discardCount[player]) != (g.deckCount[player] + g.discardCount[player])+1)
				fail = 1;
		}
		if (num_treasure == 1)
		{
			if((t.deckCount[player] + t.discardCount[player]) != (g.deckCount[player] + g.discardCount[player]))
				fail = 1;
		}
		if (num_treasure >= 2)
		{
			if((t.deckCount[player] + t.discardCount[player]) != (g.deckCount[player] + g.discardCount[player]) - 1 )
				fail = 1;
		}
		if (fail == 1)
		{
			test5_fail++;
#if (NOISY_TEST == 1)
			printf("Iteration #%d: Testing player #%d if other revealled cards are discarded failed\n", i, player);
			if (num_treasure == 0)
			{

				printf("For cards in both deck and discard piles: Expected value: %d, actual value: %d\n\n", g.deckCount[player] + g.discardCount[player], t.deckCount[player] + t.discardCount[player]);
			}
			if (num_treasure == 1)
			{
				printf("For cards in both deck and discard piles: Expected value: %d, actual value: %d\n\n", (g.deckCount[player] + g.discardCount[player]) - 1, t.deckCount[player] + t.discardCount[player]);
			}
			if (num_treasure >= 2)
			{
				printf("For cards in both deck and discard piles: Expected value: %d, actual value: %d\n\n", (g.deckCount[player] + g.discardCount[player]) - 2, t.deckCount[player] + t.discardCount[player]);
			}
#endif			
		}
		else
			test5_pass++;


	}
#if (NOISY_TEST == 1)
	printf("Random testing for playAdventurer() completed.\n");
	printf("=================================================\n\n");
	printf("test1: Testing if no supply card is changed \n");
	printf("%d out of %d tests passed!\n", test1_pass, test1_pass + test1_fail);
	printf("%d out of %d tests failed!\n\n", test1_fail, test1_pass + test1_fail);
	
	printf("test2: Testing if hand count increase properly \n");
        printf("%d out of %d tests passed!\n", test2_pass, test2_pass + test2_fail);
        printf("%d out of %d tests failed!\n\n", test2_fail, test2_pass + test2_fail);
	
	printf("test3: Testing if deck count decrease properly \n");
	printf("%d out of %d tests passed!\n", test3_pass, test3_pass + test3_fail);
        printf("%d out of %d tests failed!\n\n", test3_fail, test3_pass + test3_fail);

	printf("test4: Testing if treasure cards are added to player's hand \n");
        printf("%d out of %d tests passed!\n", test4_pass, test4_pass + test4_fail);
        printf("%d out of %d tests failed!\n\n", test4_fail, test4_pass + test4_fail);

	printf("test5: Testing if other revealled cards are discarded \n");
        printf("%d out of %d tests passed!\n", test5_pass, test5_pass + test5_fail);
        printf("%d out of %d tests failed!\n\n", test5_fail, test5_pass + test5_fail);
#endif
	return 0;

}
