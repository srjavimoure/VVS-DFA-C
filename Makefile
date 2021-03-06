# DLP - Practice 1
# Java Makefile
#
# Xoan Andreu Barro Torres (andreu.barro)
# Manoel Anton Folgueira Hernandez (manoel.folgueira)
# Uxia Ponte Villaverde (uxia.ponte.villaverde)

UNITY_ROOT=./Unity

test_exe = unity
SRC_FILES=\
  $(UNITY_ROOT)/src/unity.c \
  $(UNITY_ROOT)/extras/fixture/src/unity_fixture.c \
  State.o \
  Symbol.o \
  GenList.o \
  test/State-test.c \
  test/Symbol-test.c \
  test/GenList-test.c \
  test/test_runners/TestState_Runner.c \
  test/test_runners/TestSymbol_Runner.c \
  test/test_runners/TestGenList_Runner.c \
  test/test_runners/unity_tests.c
MOCKS_INC=-I./mocks -I./cmock/src -I./include -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src

output = out
files = source/Symbol.c source/State.c source/GenList.c source/Alphabet.c source/Transition.c source/DFA.c source/main.c
qcc = test/quickcheck4c.c
dfa_file = resources
file_example = example.dfa

all: tests compile run

performance:
	@rm -rf doc/performance.txt
	#touch doc/performance.txt
	@echo "Sin opciones añadidas (compilación normal):"
	gcc -o $(output) $(files)
	time ./$(output) -f $(dfa_file)/$(file) #>> doc/performance.txt
	@echo "Optimización básica (-O1)"
	gcc -O1 -o $(output) $(files)
	time ./$(output) -f $(dfa_file)/$(file) #>> doc/performance.txt
	@echo "Optimización recomendada (-02)"
	gcc -O2 -o $(output) $(files)
	time ./$(output) -f $(dfa_file)/$(file) #>> doc/performance.txt
	@echo "Optimización intensa (-O3)"
	gcc -O3 -o $(output) $(files)
	time ./$(output) -f $(dfa_file)/$(file) #>> doc/performance.txt
	rm $(output)

cmock:
	git clone --recursive https://github.com/throwtheswitch/cmock.git
	cd cmock
	bundle install # Ensures you have all RubyGems needed
	bundle exec rake # Run all CMock library tests
	cd ..


unity:
	git clone https://github.com/ThrowTheSwitch/Unity.git

milu:
	git clone https://github.com/yuejia/Milu

cmocks:
	@rm -rf mocks/*
	@mkdir -p mocks
	@echo "Creating mocks..."
	@ruby cmock/lib/cmock.rb -oMockConfig.yml include/Symbol.h include/State.h include/GenList.h

mutation:
	@echo "Creating mutations..."
	./Milu/bin/milu source/Symbol.c
	@echo "Creating mutations... Done"

unit: cmocks
	@echo "Compiling Symbol.c, State.c and GenList.c."
	gcc -Wall -c --coverage source/Symbol.c source/State.c source/GenList.c
	@echo "Compiling QuickCheck4c." # QuickCheck va separado para que cobertura no lo considere
	gcc -Wall -c $(qcc)
	gcc -Wall --coverage -o Symbol-qcc Symbol.o quickcheck4c.o test/Symbol-qcc.c
	gcc -Wall --coverage -o State-qcc State.o quickcheck4c.o test/State-qcc.c
	gcc -Wall --coverage -o GenList-qcc GenList.o quickcheck4c.o test/GenList-qcc.c
	@echo "Mocks for Symbol, State and GenList..."
	gcc -Wall -c $(MOCKS_INC) -DUNITY_FIXTURES mocks/MockState.c mocks/MockSymbol.c mocks/MockGenList.c
	gcc -Wall --coverage -o $(test_exe) -DUNITY_FIXTURES $(MOCKS_INC) $(SRC_FILES)
	@#gcc -Wall --coverage -o Transition-test Transition.o test/Transition-test.c
	@#gcc -Wall --coverage -o DFA-test DFA.o test/DFA-test.c
	@echo "Compiling source files... Done."

tests: unit
	@echo "Running tests..."
	@./$(test_exe) -v
	@./Symbol-qcc
	@./State-qcc
	@./GenList-qcc
	@#./Transition-test
	@#./DFA-test
	@echo "Running tests... Done."

doc: tests
	@echo "Generating documentation..."
	@# CppCheck
	@cppcheck --error-exitcode=0 $(files) -I include/ --xml 2> doc/cppcheck.xml
	@cppcheck-htmlreport --file=doc/cppcheck.xml --title=VVS-DFA-C --report-dir=doc/cppcheck
	@# Cobertura
	@rm -rf *~ unity.* unity_* *-test.g* *-qcc.g* #No consideramos cobertura para los tests
	@rm -rf *_Runner* all_tests.* #No consideramos cobertura para archivos unity
	@lcov --capture --directory . --output-file coverage.info
	@genhtml coverage.info --output-directory ./doc/coverage
	@echo "Generating documentation... Done."
	@echo "Removing temporal doc files..."
	@rm -rf doc/cppcheck.xml *~ *.o *.gcda *.gcno coverage.info
	@echo "Removing temporal doc files... Done."

run:
	@echo "Executing..."
	./$(output) -f $(dfa_file)/${file}

compile:
	@echo "Compiling..."
	gcc -o $(output) $(files)
	@echo "Compiling... Done."

clean_reports:
	@rm -rf doc/coverage doc/cppcheck
	@echo "Deleting documentation... Done."

clean:
	rm -rf *~ core $(output) $(test_exe) *-qcc *-test *.tst doc/cppcheck.xml doc/coverage *.gcda *.gcno *.o mocks/* mocks/
	@echo "Cleaning directories... Done."

