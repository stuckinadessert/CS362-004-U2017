/*
 *Description: Unit test for UpdateCoins(), It tests for the number of coins for two players with different coin 
 *
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main(){
	int i;
	int seed = 1000;
	srand(3);
	int numPlayer = 2;
	int maxBonus = 10;
	int p, r, handCount;
	int bonus;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, baron, great_hall};
	struct gameState G;

	int MAX_HAND_COUNT = 5;
	int changeIndex = 4;
	int copperCount = 5;
	int silverCount = 0;
	int goldCount = 0;
	bool allCoppers = true;

	int expected; //expected value to compare result
	int coppers[MAX_HAND_COUNT]; 
	int silvers[MAX_HAND_COUNT];
	int golds[MAX_HAND_COUNT];
	for (i = 0; i < MAX_HAND_COUNT; i++)
	{
		coppers[i] = copper;
		silvers[i] = silver;
		golds[i] = gold;
	}
	//testing coppers and silvers
#if (NOISY_TEST == 1)
	printf ("--------TESTING updateCoins():--------\n");
	printf ("TESTING updateCoins() with coppers and silvers:\n");
#endif
	for (p = 0; p < numPlayer; p++)
	{
		if (p == 1)
		{
			changeIndex = 4;
			copperCount = 5;
			silverCount = 0;
			allCoppers = true;
		}
		for (handCount = 0; handCount <= MAX_HAND_COUNT; handCount++)
		{
#if (NOISY_TEST == 1)
			bonus = rand() % maxBonus;//seeding random number for bonus
			printf("\nTest player %d with %d copper(s), %d silver(s), and %d bonus.\n", p, copperCount, silverCount, bonus);
#endif
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
			G.handCount[p] = 5;
			if(allCoppers)
			{
				memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set all the cards to copper
				allCoppers = false;
			}
			else
			{
				memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set some cards to copper
				memcpy(G.hand[p]+changeIndex, silvers, sizeof(int) * silverCount); // set some cards to silver
				changeIndex--;//dec index to add more silver
			}
			expected = copperCount + (2*silverCount) + bonus;
			copperCount--;
			silverCount++; 

			updateCoins(p, &G, bonus);
#if (NOISY_TEST ==1 )
			printf("G.coins = %d, expected = %d\n", G.coins, expected);
#endif
			assert(G.coins == expected); // check if the number of coins is correct
		}
	}
	printf ("\n");
	changeIndex = 4;
	copperCount = 5;
	silverCount = 0;
	goldCount = 0;
	allCoppers = true;

	//testing coppers and silvers
#if (NOISY_TEST == 1)
	printf ("TESTING updateCoins() with coppers and gold:\n");
#endif
	for (p = 0; p < numPlayer; p++)
	{
		if (p == 1) { //check for next player
			changeIndex = 4;
			copperCount = 5;
			goldCount = 0;
			allCoppers = true;

		}

		for (handCount = 0; handCount <= MAX_HAND_COUNT; handCount++)
		{
#if (NOISY_TEST == 1)
			bonus = rand() % maxBonus;//seeding random number for bonus
			printf("\nTest player %d with %d copper(s), %d gold(s), and %d bonus.\n", p, copperCount, goldCount, bonus);
#endif
			memset(&G, 23, sizeof(struct gameState)); // clear the game state
			r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
			G.handCount[p] = 5;
			if(allCoppers)
			{
				memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set all the cards to copper
				allCoppers = false;
			}
			else
			{
				memcpy(G.hand[p], coppers, sizeof(int) * copperCount); // set some cards to copper
				memcpy(G.hand[p]+changeIndex, golds, sizeof(int) * goldCount); // set some cards to silver
				changeIndex--;//dec index to add more silver
			}
			expected = copperCount + (3*goldCount) + bonus;
			copperCount--;
			goldCount++; 

			updateCoins(p, &G, bonus);
#if (NOISY_TEST ==1 )
			printf("G.coins = %d, expected = %d\n", G.coins, expected);
#endif
			assert(G.coins == expected); // check if the number of coins is correct
		}
	}	
	printf("All tests passed!\n");
	return 0;
}
