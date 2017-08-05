/* -----------------------------------------------------------------------
 * MORANSP EDIT
 * NOTE: This document was modified from its original version by 
 * Spencer Moran. The original document was provided as a template by
 * OSU faculty and has been modified for the sake of testing purposes.
 * 
 * Explanation of test: This particular file tests if a deck is being 
 * shuffled on each iteration. IT does this by creating a 'shadow deck' 
 * that copies the contents of the player deck before the call to 
 * shuffle(). After the call is made, a comparison is made to see
 * if there were any changes to its consistency. These tests are done
 * over different pseudorandom seeds from 1 to 1000. Failures are 
 * triggered when the contents of a shuffled deck exactly match the 
 * contents of its shadow. It is worth noting, however that simply
 * because a failure is triggered, does not imply that the function is
 * invalid. A fringe case for very small deck sizes may trigger a failure
 * condition when it exchanges identical cards or when the deck is 
 * comprised of a uniform card type. The global flags ERRFLAG and NUMTEST
 * have been added for comparison. Shuffle is invalid when ERRFLAG/NUMTEST
 * is very large as it approaches 1.
 *
 * To compile from the command line, call 'make unitTest1' and be sure to
 * include the following lines in your makefile:
 * 
 * unitTest1: unitTest1.c dominion.o rngs.o
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
#define NOISY_TEST 0

int ERRFLAG = 0;
int NUMTEST = 0;
/******************************************
 *  SafeAssertEqual -- SAE(int, int)      *
 *----------------------------------------*
 *Description: Prints to console whether  *
 * the given arguments are equal to each  *
 * other without terminating the program  *
 *****************************************/
int SAE(int L, int R){
#if(NOISY_TEST==1)
	printf("Equality check: ");
#endif
	NUMTEST++;
	if (L == R){
#if(NOISY_TEST==1)
		printf("%d == %d, PASS\n", L, R); 
#endif
		return 0;}
	else{
#if(NOISY_TEST==1)
		printf("%d == %d, FAIL - equality\n", L, R); 
#endif
		ERRFLAG++; 
		return 1;
	}
}

/******************************************
 *  SafeAssertNotEqual -- SANE(int, int)  *
 *----------------------------------------*
 *Description: Prints to console whether  *
 * the given arguments are not equal      *
 * without terminating the program        *
 *****************************************/
int SANE(int L, int R){
#if(NOISY_TEST==1)
	printf("Inequality check: ");
#endif
	NUMTEST++;
	if (L != R){
#if(NOISY_TEST==1)
		printf("%d != %d, PASS\n", L, R); 
#endif
		return 0;
	}
	else{
#if(NOISY_TEST==1)
printf("%d != %d, FAIL - Inequality\n", L, R); 
#endif
		ERRFLAG++; 
		return 1;}
}


int main() {
    int i;
    int j;
    int testDeck[MAX_DECK];
    int diffCount; 
    int seed = 1000;
    int numPlayer = 4; //MAX_PLAYERS;
    int maxBonus = 10;
    int p, r, handCount;
    int bonus;
    int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
    struct gameState G;
    int maxHandCount = 5;
    // arrays of all coppers, silvers, and golds
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    for (i = 0; i < MAX_HAND; i++)
    {
        coppers[i] = copper;
        silvers[i] = silver;
        golds[i] = gold;
    }

    //printf("Testing Assert Function\n");
    //SAE(1,1);

//Function test 1. To check the shuffle command, ensure that the
// cards before and after the call are not equal.
int z;
    printf ("-----------------------------------\n");
    printf ("TESTING shuffle() 1000 iterations:\n");
for (z=1;z<seed;z++){
    memset(&G, 23, sizeof(struct gameState));   // clear the game state    ::LEGACY
    r = initializeGame(numPlayer, k, z, &G); 	// initialize a new game   ::LEGACY
    G.handCount[p] = handCount;                 // set the number of cards ::LEGACY

#if(NOISY_TEST==1)
printf("The size of each deck is: %d\n",G.deckCount[0]);

for (i=0;i<G.deckCount[0]; i++){
	printf("P1 card:%d\n",G.deck[0][i]);
}

for (i=0;i<G.deckCount[1]; i++){
	printf("P2 card:%d\n",G.deck[1][i]);
}

for (i=0;i<G.deckCount[2]; i++){
	printf("P3 card:%d\n",G.deck[2][i]);
}

for (i=0;i<G.deckCount[3]; i++){
	printf("P4 card:%d\n",G.deck[3][i]);
}
#endif

//Tester's Note: There is a chance, albeit slim, that a deck could be shuffled 
// such that the order of cards in the deck does not change. For example, 
// the instance where every card in a deck is the same or replaces an identical card.

for (i = 0; i < numPlayer; i++){
	diffCount = 0;
#if(NOISY_TEST==1)
	printf("Player %d deck\n", i+1);
#endif
	for(j = 0; j < G.deckCount[i]; j++){
		testDeck[j] = G.deck[i][j];	
	}
	for(j = 0; j < G.deckCount[i]; j++){
		SAE(testDeck[j], G.deck[i][j]); 	//comparison deck matches deck being shuffled.
	}
	shuffle(i,&G); 					//Shuffle call
	for (j = 0; j < G.deckCount[i]; j++){
		if(testDeck[j] != G.deck[i][j]){
			diffCount++;
		}
	}
	SANE(0,diffCount); 				//Sanity check. If both equal, a bug might exist.
}
}
    if (ERRFLAG != 0){ printf("\nFound %d failures out of %d comparisons\n",ERRFLAG, NUMTEST);}
    else{ printf("All tests passed!\n");}

    return 0;
}
