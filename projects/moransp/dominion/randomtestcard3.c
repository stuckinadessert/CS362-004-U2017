 
/* NOTE: This document was modified from its original version by 
 * Spencer Moran. The original document was provided as a template by
 * OSU faculty and has been modified for the sake of testing purposes.
 * 
 * To compile from the command line, call 'make cardtest4' and be sure to
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
		printf("%sFAIL - Expected value: %d, Actual: %d%s\n",KRED, xval, aval,KNRM);
#endif
		return 1;
	}
#if (NOISY_TEST ==1)
	printf("%sPASS - Expected value:%d, Actual:%d%s\n",KGRN, xval, aval,KNRM);
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
    int testinterval = 0;
    int status;
    int i;
    int run=1;
    int seed=1;
    int handcounta;
    int handcountb;
    int discardpile;
    int numActions=0;
	memset(&G, 23,sizeof(struct gameState));
    	initializeGame(4, k, 1, &G);
    int currentPlayer = whoseTurn(&G);

	printf("\n------TESTING card: Village------\n");
	while (run !=0){
		//Init block to guarantee new random seed
		printf("Interval:%d\n", testinterval);
		seed = rand()%10000+1;
		printf("current seed value: %d\n", seed);
		memset(&G,23,sizeof(struct gameState));
		initializeGame(4,k,seed, &G);
		for (i=0; i<2; i++)
		{
			testinterval++;
			handcounta = G.handCount[currentPlayer];
			discardpile = G.discardCount[currentPlayer];
			numActions = G.numActions;
			status = dom_village(0, currentPlayer, &G);
			bugtracker += expected(0,status,"status return 0");	
			handcountb = G.handCount[currentPlayer];
			bugtracker += expected(handcounta,handcountb, "handcounta == handcountb");
			bugtracker += expected(numActions+1, G.numActions, "numActions increased by 1");
			bugtracker += expected(discardpile+1, G.discardCount[currentPlayer], "discardpile + 1");
		}		
		if (testinterval >= 100){
			run = 0;
		}
	}


printf("%sfound:%d errors out of %d intervals\n",KNRM,bugtracker, testinterval);
return 0;
}

