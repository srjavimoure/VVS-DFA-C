# DLP - Practice 1
# Java Makefile
#
# Xoan Andreu Barro Torres (andreu.barro)
# Manoel Anton Folgueira Hernandez (manoel.folgueira)
# Uxia Ponte Villaverde (uxia.ponte.villaverde)

output = out
files = Symbol.c State.c GenList.c Alphabet.c Transition.c DFA.c main.c
dfa_file = resources/example.dfa

cunit:
	gcc -Wall -Werror -c --coverage $(files)
	gcc -Wall -Werror --coverage -o Symbol-test Symbol.o Symbol-test.c -lcunit
	gcc -Wall -Werror --coverage -o State-test State.o State-test.c -lcunit
	gcc -Wall -Werror --coverage -o GenList-test GenList.o GenList-test.c -lcunit
	gcc -Wall -Werror --coverage -o Transition-test Transition.o Transition-test.c -lcunit
	gcc -Wall -Werror --coverage -o DFA-test DFA.o DFA-test.c -lcunit

test:
	make cunit
	./Symbol-test
	./State-test
	./GenList-test
	./Transition-test
	./DFA-test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory coverage	

run:
	./$(output) -f $(dfa_file)

compile:
	gcc -o $(output) $(files)

clean:
	rm -rf *~ *.o core $(output) *-test *.tst coverage coverage.info *.gcno *.gcda

all:
	make test
	make compile
	make run
