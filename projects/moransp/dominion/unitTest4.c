 
/* NOTE: This document was modified from its original version by 
 * Spencer Moran. The original document was provided as a template by
 * OSU faculty and has been modified for the sake of testing purposes.
 * 
 * Explanation of test: This unit test measures the expected state of
 * the gameState object after the function endTurn() is called.
 *
 * To compile from the command line, call 'make unitTest4' and be sure to
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
    int i;
	printf("\n------TESTING endTurn()------\n");
	memset(&G, 23,sizeof(struct gameState));
    	initializeGame(4, k, 1000, &G);
   
	for (i=0;i<G.numPlayers;i++)
	{
	#if (NOISY_TEST==1)

		printf("********************************\n");
		printf("it is currently player %d's turn\n", G.whoseTurn);
	#endif
		endTurn(&G);
	#if (NOISY_TEST==1)
		printf("-------------------------------\n");
		printf("ending turn...\t\n");
		printf("-------------------------------\n");
	#endif
		if (i==G.numPlayers-1){
			bugtracker += expected(0, G.whoseTurn);
		}	
		else {
			bugtracker += expected(i+1, G.whoseTurn);
		}
	#if (NOISY_TEST==1)
		printf("phase\t\t");
	#endif
		bugtracker += expected(0, G.phase);
	#if (NOISY_TEST==1)
		printf("numActions\t");
	#endif
		bugtracker += expected(1,G.numActions);
	#if (NOISY_TEST==1)
		printf("numBuys\t\t");
	#endif
		bugtracker += 	expected(1,G.numBuys);
	#if (NOISY_TEST==1)
		printf("playedCardCount\t");
	#endif
		bugtracker += expected(0,G.playedCardCount);
	#if (NOISY_TEST==1)
		printf("handCount\t");
	#endif
		bugtracker += expected(0,G.handCount[i]);
	#if (NOISY_TEST==1)
		printf("coins\t\t");
	#endif
		bugtracker += expected(3,G.coins);
	}
		
	printf("Failures found:%d\n", bugtracker);
	if (bugtracker == 0){
		printf("\nendTurn() All Tests Passed\n");
	}
return 0;
}
