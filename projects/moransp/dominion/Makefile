CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

unitTest1: unitTest1.c dominion.o rngs.o
	gcc -o unitTest1 -g unitTest1.c dominion.o rngs.o $(CFLAGS)

unitTest2: unitTest2.c dominion.o rngs.o
	gcc -o unitTest2 -g unitTest2.c dominion.o rngs.o $(CFLAGS)

runmytests: unitTest1 unitTest2
	./unitTest1 &> unittestresult.out
	gcov unitTest1.c >> unittestresult.out
	cat unittest1.c.gcov >> unittestresult.out	
	./unitTest2 &> unittestresult.out
	gcov unitTest2.c >> unittestresult.out
	cat unittest2.c.gcov >> unittestresult.out	

testTemplate: testTemplate.c dominion.o rngs.o
	gcc -o testTemplate -g testTemplate.c dominion.o rngs.o $(CFLAGS)

cardtest4: democardtest4.c dominion.o rngs.o
	gcc -o democardtest1 -g democardtest4.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
