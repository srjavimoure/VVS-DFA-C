# DLP - Practice 1
# Java Makefile
#
# Xoan Andreu Barro Torres (andreu.barro)
# Manoel Anton Folgueira Hernandez (manoel.folgueira)
# Uxia Ponte Villaverde (uxia.ponte.villaverde)

output = out
files = source/Symbol.c source/State.c source/GenList.c source/Alphabet.c source/Transition.c source/DFA.c source/main.c
dfa_file = resources/example.dfa

cunit:
	gcc -Wall -c --coverage $(files)
	gcc -Wall --coverage -o Symbol-test Symbol.o test/Symbol-test.c -lcunit
	gcc -Wall --coverage -o State-test State.o test/State-test.c -lcunit
	gcc -Wall --coverage -o GenList-test GenList.o test/GenList-test.c -lcunit
	#gcc -Wall --coverage -o Transition-test Transition.o test/Transition-test.c -lcunit
	#gcc -Wall --coverage -o DFA-test DFA.o test/DFA-test.c -lcunit
	rm -rf *~ *.o

tests:
	make cunit
	./Symbol-test
	./State-test
	./GenList-test
	#./Transition-test
	#./DFA-test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ./doc/coverage
	rm -rf *~ *.gcda *.gcno coverage.info

run:
	./$(output) -f $(dfa_file)

compile:
	gcc -o $(output) $(files)

clean:
	rm -rf *~ *.o core $(output) *-test *.tst doc/coverage coverage.info *.gcno *.gcda

all:
	make test
	make compile
	make run
