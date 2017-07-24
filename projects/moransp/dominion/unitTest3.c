/* -----------------------------------------------------------------------
 * MORANSP EDIT
 * NOTE: This document was modified from its original version by 
 * Spencer Moran. The original document was provided as a template by
 * OSU faculty and has been modified for the sake of testing purposes.
 * 
 * Explanation of test: This unit test checks the output of the getCost() 
 * function when it is fed numbers from 1 to 27 and is compared to known 
 * correct outputs. It also checks against bad information including
 * negative numbers and numbers outside of its intended range. due to the
 * functions small size, this test can provide full statement coverage
 * for all reasonable cases.
 * 
 * To compile from the command line, call 'make unitTest3' and be sure to
 * include the following lines in your makefile:
 * 
 * unitTest2: unitTest3.c dominion.o rngs.o
 *      gcc -o unitTest3 -g  unitTest1.c dominion.o rngs.o $(CFLAGS)
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

int main(){
	int i;
	int costs[27]={0,2,5,8,0,3,6,6,5,4,4,5,4,4,3,4,3,5,3,5,3,4,2,5,4,4,4};
	int bugtracker =0;
	for (i=0; i<27;i++)
	{
		bugtracker += expected(costs[i],getCost(i));
	}
	bugtracker+=expected(0,getCost(curse));
	bugtracker+=expected(-1,getCost(37));
	bugtracker+=expected(-1,getCost(-4));
	printf("Values checked report(s) %d errors\n", bugtracker);
	if (bugtracker == 0){
		printf("All tests passed\n");
	}
	else {
		printf("Completed with errors\n");
	}
	return 0;
}
