/*
 *Description: Unit test for isGameover()
 *Test#1: the game without any change; 
 *Test#2: the game with 0 provinces; 
 *Test#3: The supply card has one empty pile; 
 *Test#4: The supply card has two empty pile; Test#4: The supply card has three empty pile.
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
	int seed = 1000; // random seed
	int numPlayer = 2; 
	int r;
	int k[10] = {adventurer, council_room, feast, gardens, mine, remodel, smithy, village, tribute, embargo};
	struct gameState G;
	int result;
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

#if (NOISY_TEST == 1)
	printf("\n--------TESTING isGameOver():--------\n");
	printf("If the game ends, isGameOver = 1\n");
#endif

	//test#1: game without any change
	result = isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Test#1: The game without any change\n");
	printf("Game is over: %d, expected: 0\n\n", result);	
#endif
	assert(result == 0);
/*
	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game
*/
	//test with 0 provinces
	G.supplyCount[province] = 0;
	result = isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Test#2: 0 Provinces\n");
	printf("Game is over: %d, expected: 1\n\n", result);
#endif
	assert(result == 1); //expect to end

	memset(&G, 23, sizeof(struct gameState));   // clear the game state
	r = initializeGame(numPlayer, k, seed, &G); // initialize a new game

	//test with one empty pile in deck
	G.supplyCount[smithy] = 0;
	result = isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Test#3: 1 Empty pile\n");
	printf("Game is over: %d, expected: 0\n\n", result);
#endif
	assert(result == 0);

	//test with two empty piles in deck
	G.supplyCount[adventurer] = 0;
	result = isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Test#4: 2 Empty piles\n");
	printf("Game is over: %d, expected: 0\n\n", result);
#endif
	assert(result == 0);
	
	//test with three empty piles in deck
	G.supplyCount[village] = 0;
	result = isGameOver(&G);
#if (NOISY_TEST == 1)
	printf("Test#5: 3 Empty piles\n");
	printf("Game is over: %d, expected: 1\n\n", result);
#endif
	assert(result == 1);//expect to end


	printf("All tests passed!\n");

	return 0;

}	








