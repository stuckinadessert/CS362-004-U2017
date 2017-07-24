 
/* NOTE: This document was modified from its original version by 
 * Spencer Moran. The original document was provided as a template by
 * OSU faculty and has been modified for the sake of testing purposes.
 * 
 * To compile from the command line, call 'make cardtest3' and be sure to
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
    	initializeGame(2, k, 1000, &G);

	printf("\n------TESTING card: Village()------\n");
	status = dom_village(1, G.whoseTurn, &G);
	bugtracker += expected(5,G.handCount[G.whoseTurn], "Current player hand count.");
	bugtracker += expected(1,G.discardCount[G.whoseTurn], "Current player discard count.");
	bugtracker += expected(2,G.numActions,"Current player actions remaining.");
	for (i=1;i<G.numPlayers;i++){
		bugtracker += expected(0,G.handCount[i], "Other player hand count.");
		bugtracker += expected(0,G.discardCount[i], "Other player discard count.");

	}
printf("%s\n",KNRM);
return 0;
}
