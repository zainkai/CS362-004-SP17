CFLAGS = -Wall -fpic -coverage -lm

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)

testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

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

randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestadventurer.c rngs.o -o randomtestadventurer -lm -g -fno-stack-protector -fno-stack-protector

randomtestcard1: randomtestcard1.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestcard1.c rngs.o -o randomtestcard1 -lm -g -fno-stack-protector -fno-stack-protector

randomtestcard2: randomtestcard2.c dominion.o rngs.o
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o randomtestcard2.c rngs.o -o randomtestcard2 -lm -g -fno-stack-protector -fno-stack-protector

randomtestall: randomtestadventurer randomtestcard1 randomtestcard2

runrandomtests: randomtestall
	#randomtestadventurer
	./randomtestadventurer > randomtestadventurer.out
	gcov dominion.c >> randomtestadventurer.out
	cat dominion.c.gcov >> randomtestadventurer.out
	#randomtestcard1
	./randomtestcard1 > randomtestcard1.out
	gcov dominion.c >> randomtestcard1.out
	cat dominion.c.gcov >> randomtestcard1.out
	#randomtestcard2
	./randomtestcard2 > randomtestcard2.out
	gcov dominion.c >> randomtestcard2.out
	cat dominion.c.gcov >> randomtestcard2.out

cardtest1:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest1.c rngs.o -o cardtest1 -lm -g -DNDEBUG
cardtest2:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest2.c rngs.o -o cardtest2 -lm -g -DNDEBUG
cardtest3:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest3.c rngs.o -o cardtest3 -lm -g -DNDEBUG
cardtest4:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest4.c rngs.o -o cardtest4 -lm -g -DNDEBUG
cardtest5:
	gcc -fprofile-arcs -ftest-coverage -Wall -std=c99 dominion.o cardtest5.c rngs.o -o cardtest5 -lm -g -DNDEBUG
cardtestall: cardtest1 cardtest2 cardtest3 cardtest4 cardtest5

unittestresults.out: cardtest1 cardtest2 cardtest3 cardtest4 cardtest5
	./cardtest1 > unittestresult.out
	./cardtest2 >> unittestresult.out
	./cardtest3 >> unittestresult.out
	./cardtest4 >> unittestresult.out
	./cardtest5 >> unittestresult.out

player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player testDrawCard testBuyCard badTestDrawCard randomtestall

clean:
	rm -f *.o playdom.exe playdom test.exe test player player.exe testInit testInit.exe *.gcov *.gcda *.gcno *.so
