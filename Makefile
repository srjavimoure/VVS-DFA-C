# DLP - Practice 1
# Java Makefile
#
# Xoan Andreu Barro Torres (andreu.barro)
# Manoel Anton Folgueira Hernandez (manoel.folgueira)
# Uxia Ponte Villaverde (uxia.ponte.villaverde)

UNITY_ROOT=./Unity

unity_tests = unity
SRC_FILES=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  State.o \
  Symbol.o \
  test/State-test.c \
  test/Symbol-test.c \
  test/test_runners/TestState_Runner.c \
  test/test_runners/TestSymbol_Runner.c \
  test/test_runners/all_tests.c
INC_DIRS=-Iinclude -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src

output = out
files = source/Symbol.c source/State.c source/GenList.c source/Alphabet.c source/Transition.c source/DFA.c source/main.c
qcc = test/quickcheck4c.c
dfa_file = resources
file_example = example.dfa

all: tests compile run

cunit:
	gcc -Wall -c --coverage $(files)
	gcc -Wall -c $(qcc) # QuickCheck va separado para que cobertura no lo considere
	gcc -Wall --coverage -o $(unity_tests) -DUNITY_FIXTURES $(INC_DIRS) $(SRC_FILES) -lcunit
	gcc -Wall --coverage -o Symbol-qcc Symbol.o quickcheck4c.o test/Symbol-qcc.c -lcunit
	gcc -Wall --coverage -o State-qcc State.o quickcheck4c.o test/State-qcc.c -lcunit
	gcc -Wall --coverage -o GenList-test GenList.o quickcheck4c.o test/GenList-test.c -lcunit
	@#gcc -Wall --coverage -o Transition-test Transition.o test/Transition-test.c -lcunit
	@#gcc -Wall --coverage -o DFA-test DFA.o test/DFA-test.c -lcunit

doc: tests
	@# CppCheck
	cppcheck --error-exitcode=0 $(files) -I include/ --xml 2> doc/cppcheck.xml
	cppcheck-htmlreport --file=doc/cppcheck.xml --title=VVS-DFA-C --report-dir=doc/cppcheck
	@# Cobertura
	rm -rf *~ unity.* unity_* *-test.g* *-qcc.g* #No consideramos cobertura para los tests
	rm -rf *_Runner* all_tests.* #No consideramos cobertura para archivos unity
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory ./doc/coverage
	#rm -rf doc/cppcheck.xml *~ *.o *.gcda *.gcno coverage.info

tests: cunit
	@./$(unity_tests) -v
	@./Symbol-qcc
	@./State-qcc
	@./GenList-test
	@#@./Transition-test
	@#@./DFA-test

run:
	./$(output) -f $(dfa_file)/${file}

example: compile
	./$(output) -f $(dfa_file)/$(file_example)

compile:
	gcc -o $(output) $(files)

clean_reports:
	rm -rf doc/coverage doc/cppcheck

clean:
	rm -rf *~ core $(output) $(unity_tests) *-qcc *-test *.tst doc/cppcheck.xml doc/coverage *.gcda *.gcno *.o

