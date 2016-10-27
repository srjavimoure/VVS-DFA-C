# DLP - Practice 1
# Java Makefile
#
# Xoan Andreu Barro Torres (andreu.barro)
# Manoel Anton Folgueira Hernandez (manoel.folgueira)
# Uxia Ponte Villaverde (uxia.ponte.villaverde)

output = out
files = source/Symbol.c source/State.c source/GenList.c source/Alphabet.c source/Transition.c source/DFA.c source/main.c
qcc = test/quickcheck4c.c
dfa_file = resources/example.dfa

cunit:
	gcc -Wall -c --coverage $(files) $(qcc)
	gcc -Wall --coverage -o Symbol-test Symbol.o quickcheck4c.o test/Symbol-test.c -lcunit
	#gcc -Wall --coverage -o State-test State.o test/State-test.c -lcunit
	#gcc -Wall --coverage -o GenList-test GenList.o test/GenList-test.c -lcunit
	#gcc -Wall --coverage -o Transition-test Transition.o test/Transition-test.c -lcunit
	#gcc -Wall --coverage -o DFA-test DFA.o test/DFA-test.c -lcunit
	rm -rf *~

doc:
	cppcheck --error-exitcode=0 $(files) -I include/ --xml 2> doc/cppcheck.xml
	cppcheck-htmlreport --file=doc/cppcheck.xml --title=VVS-DFA-C --report-dir=doc/cppcheck
	rm doc/cppcheck.xml

tests: cunit
	./Symbol-test
	#./State-test
	#./GenList-test
	#./Transition-test
	#./DFA-test
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ./doc/coverage
	rm -rf *~ *.o *.gcda *.gcno coverage.info

run:
	./$(output) -f $(dfa_file)

compile:
	gcc -o $(output) $(files)

clean_reports:
	rm -rf doc/coverage doc/cppcheck

clean:
	rm -rf *~ core $(output) *-test *.tst doc/cppcheck.xml *.gcda *.gcno *.o
all:
	make test
	make compile
	make run
