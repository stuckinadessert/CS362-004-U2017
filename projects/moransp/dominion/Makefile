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

runtestsold: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testUpdateCoins: testUpdateCoins.c dominion.o rngs.o
	gcc -o testUpdateCoins -g testUpdateCoins.c dominion.o rngs.o $(CFLAGS)

unitTest1: unitTest1.c dominion.o rngs.o
	gcc -o unitTest1 -g unitTest1.c dominion.o rngs.o $(CFLAGS)

unitTest2: unitTest2.c dominion.o rngs.o
	gcc -o unitTest2 -g unitTest2.c dominion.o rngs.o $(CFLAGS)

unitTest3: unitTest3.c dominion.o rngs.o
	gcc -o unitTest3 -g unitTest3.c dominion.o rngs.o $(CFLAGS)

unitTest4: unitTest4.c dominion.o rngs.o
	gcc -o unitTest4 -g unitTest4.c dominion.o rngs.o $(CFLAGS)

cardtest1: cardtest1.c dominion.o rngs.o
	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest2: cardtest2.c dominion.o rngs.o
	gcc -o cardtest2 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest3: cardtest3.c dominion.o rngs.o
	gcc -o cardtest3 -g cardtest1.c dominion.o rngs.o $(CFLAGS)

cardtest4: cardtest4.c dominion.o rngs.o
	gcc -o cardtest4 -g cardtest1.c dominion.o rngs.o $(CFLAGS)


runtests: unitTest1 unitTest2 unitTest3 unitTest4 cardtest1 cardtest2 cardtest3 cardtest4
	./unitTest1 &> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./unitTest2 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./unitTest3 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./unitTest4 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./cardtest1 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./cardtest2 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./cardtest3 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out
	./cardtest4 >> unittestresult.out
	gcov -b -c dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

testTemplate: testTemplate.c dominion.o rngs.o
	gcc -o testTemplate -g testTemplate.c dominion.o rngs.o $(CFLAGS)

democardtest4: democardtest4.c dominion.o rngs.o
	gcc -o democardtest1 -g democardtest4.c dominion.o rngs.o $(CFLAGS)

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe cardtest1.exe cardtest2.exe cardtest3.exe cardtest4.exe unitTest1.exe unitTest2.exe unitTest3.exe unitTest4.exe
