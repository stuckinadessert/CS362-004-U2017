/*
 *Description: fullDeckCount()
 *The test calculate the full deckcount after putting a set of cards into different piles. 
 */
#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1

int main() {
	int i;
	int seed = 1000;
	int numPlayer = 2;
	int p, r;
	int result;
	int count;
	int copperCount;
	int estateCount;
	int k[10] = {adventurer, great_hall, feast, gardens, mine, remodel, smithy, village, tribute, embargo};   
	struct gameState G;

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
#if (NOISY_TEST ==1)
	printf("\n--------TESTING fullDeckCount():--------\n");
#endif

	for (p = 0; p< numPlayer; p++)
	{
#if (NOISY_TEST == 1)
		printf("\nTesting for Player %d:\n", p);// player 0 then player 1
		printf("Adding the following to the\n");
		printf("deck:         6 coppers\n");
		printf("hand:         8 golds\n");
		printf("discard pile: 3 provinces\n");
		printf("deck:         4 smithys\n");
		printf("hand:	      5 Minion\n");
		printf("deck:         4 Cutpurse\n");
		printf("Test results:\n");
#endif	
		copperCount = 7; //initial coppercount
		result = fullDeckCount(p, 4, &G);		
#if (NOISY_TEST == 1)
		printf("initial copper result: %d, expected: %d\n", result, copperCount); 
#endif	
		assert(result == copperCount);

		estateCount = 3; //initial estateCount
		result = fullDeckCount(p, 1, &G);
#if (NOISY_TEST == 1)
		printf("initial estate result: %d, expected: %d\n", result, estateCount);
#endif
		assert(result == estateCount);

		//test the updated copperCount
		count = 6;
		copperCount = copperCount + count;
		for(i=0; i < count; i++)
		{
			G.deck[p][ G.deckCount[p] ] = copper;
			G.deckCount[p]++;
		}
		result = fullDeckCount(p, 4, &G);
#if (NOISY_TEST == 1)
		printf("updated copper result: %d, expected: %d\n", result, copperCount);
#endif
		assert(result == copperCount);

		//test the gold(hand)
		count = 8;
		for(i=0; i < count; i++)
		{
			G.hand[p][ G.handCount[p] ] = gold;
			G.handCount[p]++;
		}
		result = fullDeckCount(p, 6, &G);
#if (NOISY_TEST == 1)
		printf("gold result: %d, expected: %d\n", result, count);
#endif
		assert(result == count);
		
		//test the provinces(discard pile)
		count = 3;
		for(i=0; i < count; i++)
		{
			G.discard[p][ G.discardCount[p] ] = province;
			G.discardCount[p]++;
		}
		result = fullDeckCount(p, 3, &G);
#if (NOISY_TEST == 1)
		printf("provinces result: %d, expected: %d\n", result, count);
#endif
		assert(result == count);

		
		//test the smithys(deck)
		count = 4;
		for(i=0; i < count; i++)
		{
			G.deck[p][ G.deckCount[p] ] = smithy;
			G.deckCount[p]++;
		}
		result = fullDeckCount(p, 13, &G);
#if (NOISY_TEST == 1)
		printf("smithy result: %d, expected: %d\n", result, count);
#endif
		assert(result == count);

		
		//test the Minion(hand)
		count = 5;
		for(i=0; i < count; i++)
		{
			G.hand[p][ G.handCount[p] ] = minion;
			G.handCount[p]++;
		}
		result = fullDeckCount(p, 17, &G);
#if (NOISY_TEST == 1)
		printf("minion result: %d, expected: %d\n", result, count);
#endif
		assert(result == count);

		
		//test the cutpurse(deck)
		count = 4;
		for(i=0; i < count; i++)
		{
			G.deck[p][ G.deckCount[p] ] = cutpurse;
			G.deckCount[p]++;
		}
		result = fullDeckCount(p, 21, &G);
#if (NOISY_TEST == 1)
		printf("cutpurse result: %d, expected: %d\n", result, count);
#endif
		assert(result == count);
	}
	/*	result = fullDeckCount(0, 13, &G);
#if (NOISY_TEST == 1)
printf("smithy result: %d\n",result);
#endif
*/
	printf("\nAll tests passed!!\n");
	return 0;

}
