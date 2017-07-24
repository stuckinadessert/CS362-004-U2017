/* -----------------------------------------------------------------------
 * MORANSP EDIT
 * NOTE: This document was modified from its original version by 
 * Spencer Moran. The original document was provided as a template by
 * OSU faculty and has been modified for the sake of testing purposes.
 * 
 * Explanation of test: This unit test measures the expected outputs 
 * against a range of common cards. It examines the state of the game
 * before and after each call, specifically the values that are affected
 * by the call. 
 * To compile from the command line, call 'make unitTest2' and be sure to
 * include the following lines in your makefile:
 * 
 * unitTest2: unitTest2.c dominion.o rngs.o
 *      gcc -o unitTest1 -g  unitTest1.c dominion.o rngs.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
int expected(int xval, int aval){

	if (xval != aval){
#if (NOISY_TEST ==1)
		printf("FAIL - Expected value: %d, Actual: %d\n", xval, aval);
#endif
		return 1;
	}
#if (NOISY_TEST ==1)
	printf("PASS - Expected value:%d, Actual:%d\n", xval, aval);
#endif
	return 0;
}

int main() {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int bugtracker = 0;
    int status = 0;
    int cardCost[10]= {6,4,2,3,5,5,4,4,5,4};
    int i=0;
    int supply;
    int coins;
    int buys;
printf("\n------TESTING buyCard()------\n");
for (i=0; i<10; i++){
	memset(&G, 23,sizeof(struct gameState));
    	initializeGame(2, k, 1000, &G);
   /* 
	printf("initial gameState:\n");
	printf("num players:%d\n", G.numPlayers);
	printf("supplyCount:%d\n", G.supplyCount[0]);
	printf("supplyCount:%d\n", G.supplyCount[1]);
	printf("embargoTokens:%d\n", G.embargoTokens[0]);
	printf("outpostPlayed:%d\n", G.outpostPlayed);
	printf("outpostTurn:%d\n", G.outpostTurn);
	printf("whoseTurn:%d\n", G.whoseTurn);
	printf("phase:%d\n", G.phase);
	printf("numActions:%d\n", G.numActions);
	printf("coins:%d\n",G.coins);
	printf("numBuys:%d\n",G.numBuys);
	printf("hand:%d\n",G.hand[0][0]);
	printf("handCount:%d\n", G.handCount[0]);
	printf("deck:%d\n", G.deck[0][0]);
	printf("deckCount:%d\n", G.deckCount[0]);
	printf("discard:%d\n", G.discard[0][0]);
	printf("discardCount:%d\n", G.discardCount[0]);
	printf("playedCards:%d\n", G.playedCards[0]);
	printf("playedCardCount:%d\n", G.playedCardCount);
*/
#if (NOISY_TEST==1)
	printf("********************************\n");
	printf("State prior to buy card\n");
	printf("Coins:%d\n",G.coins);
	printf("supplyCount:%d\n", G.supplyCount[k[i]]);
	printf("numBuys:%d\n", G.numBuys);
#endif
	coins = G.coins;
	supply = G.supplyCount[k[i]];
	buys = G.numBuys;
#if (NOISY_TEST==1)
	printf("-------------------------------\n");
	printf("buying card...");
#endif
	status = buyCard(k[i],&G);
	if (status != 0)
	{
#if (NOISY_TEST==1)
		printf("Could not buy\n");
		printf("Coins:%d\n",G.coins);
#endif
		bugtracker += expected(coins,G.coins);
#if (NOISY_TEST==1)
		printf("supplyCount:%d\n", G.supplyCount[k[i]]);
#endif
		bugtracker += expected(supply,G.supplyCount[k[i]]);
#if (NOISY_TEST==1)
		printf("numBuys:%d\n", G.numBuys);
#endif
		bugtracker += expected(buys, G.numBuys);
	}
	else{
#if (NOISY_TEST==1)
		printf("purchase made\n");
		printf("Coins:%d\n",G.coins);
#endif
		bugtracker += expected((coins-cardCost[i]),G.coins);
#if (NOISY_TEST==1)
		printf("supplyCount:%d\n", G.supplyCount[k[i]]);
#endif
		bugtracker += expected(supply-1,G.supplyCount[k[i]]);
#if (NOISY_TEST==1)
		printf("numBuys:%d\n", G.numBuys);
#endif
		bugtracker += expected(buys-1, G.numBuys);	
	}
}
	printf("Failures found:%d\n", bugtracker);
	if (bugtracker == 0){
		printf("\nbuyCard() All Tests Passed\n");
	}
    return 0;
}
