 
/* NOTE: This document was modified from its original version by 
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

#define KNRM "\x1B[0m"
#define KRED "\x1B[31m"
#define KGRN "\x1B[32m"
#define KCYN "\x1B[36m"
// set NOISY_TEST to 0 to remove printfs from output
#define NOISY_TEST 1
int expected(int xval, int aval, char *msg){
#if (NOISY_TEST==1)
	printf("%sTESTING:%s %s---\n",KCYN,KNRM,msg);
#endif
	if (xval != aval){
#if (NOISY_TEST ==1)
		printf("%sFAIL - Expected value: %d, Actual: %d\n",KRED, xval, aval);
#endif
		return 1;
	}
#if (NOISY_TEST ==1)
	printf("%sPASS - Expected value:%d, Actual:%d\n",KGRN, xval, aval);
#endif
	return 0;
}
/****************************************
 *REFERENCE: gameState object

   int numPlayers; //number of players
   int supplyCount[treasure_map+1]; //amount of specific card given a number.
   int embargoTokens[treasure_map+1];
   int outpostPlayed;
   int outpostTurn;
   int whoseTurn;
   int phase;
   int numActions; //starts at 1 each turn
   int coins; // Use as you see fit! 
   int numBuys; // Starts at 1 each turn 
   int hand[MAX_PLAYERS][MAX_HAND];
   int handCount[MAX_PLAYERS];
   int deck[MAX_PLAYERS][MAX_DECK];
   int deckCount[MAX_PLAYERS];
   int discard[MAX_PLAYERS][MAX_DECK];
   int discardCount[MAX_PLAYERS];
   int playedCards[MAX_DECK];
   int playedCardCount;
 * */
int main() {
    struct gameState G;
    int k[10] = {adventurer, gardens, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy};
    int bugtracker = 0;
    int status;
    int i;
	memset(&G, 23,sizeof(struct gameState));
    	initializeGame(4, k, 1000, &G);

	printf("\n------TESTING card: Embargo()------\n");
	status = dom_embargo(1,1, G.whoseTurn, &G);
	bugtracker += expected(0,status, "Return status");
	bugtracker += expected(4,G.handCount[G.whoseTurn], "Current player hand count.");
	bugtracker += expected(1,G.discardCount[G.whoseTurn], "Current player discard count.");
	bugtracker += expected(0,G.numActions,"Current player actions remaining.");
	bugtracker += expected(6,G.coins, "Current Player coins");
	bugtracker += expected(1,G.embargoTokens[1], "embargoTokens increments");
	for (i=1;i<G.numPlayers;i++){
		bugtracker += expected(0,G.handCount[i], "Other player hand count.");
		bugtracker += expected(0,G.discardCount[i], "Other player discard count.");

	}

printf("%sfound:%d errors.\n",KNRM,bugtracker);
return 0;
}

