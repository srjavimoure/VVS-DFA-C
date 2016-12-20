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
  GenList.o \
  Transition.o \
  test/State-test.c \
  test/Symbol-test.c \
  test/GenList-test.c \
  test/Transition-test.c \
  mocks/MockSymbol.c \
  mocks/MockState.c \
  mocks/MockGenList.c \
  test/test_runners/TestState_Runner.c \
  test/test_runners/TestSymbol_Runner.c \
  test/test_runners/TestGenList_Runner.c \
  test/test_runners/TestTransition_Runner.c \
  test/test_runners/all_tests.c
INC_DIRS=-Imocks -Iinclude -I$(UNITY_ROOT)/src -I$(UNITY_ROOT)/extras/fixture/src

output = out
files = source/Symbol.c source/State.c source/GenList.c source/Alphabet.c source/Transition.c source/DFA.c source/main.c
qcc = test/quickcheck4c.c
dfa_file = resources
file_example = example.dfa

all: tests compile run

cmock:
	git clone --recursive https://github.com/throwtheswitch/cmock.git
	cd cmock
	bundle install # Ensures you have all RubyGems needed
	bundle exec rake # Run all CMock library tests
	cd ..


unity: cmock
	git clone https://github.com/ThrowTheSwitch/Unity.git

milu:
	git clone https://github.com/yuejia/Milu

mocks:
	mkdir mocks
	ruby cmock/lib/cmock.rb -oMockConfig.yml include/Symbol.h include/State.h include/GenList.h

mutation:
	@echo "Creating mutations..."
	./Milu/bin/milu source/Symbol.c
	@echo "Creating mutations... Done"

cunit: mocks
	@echo "Compiling source files..."
	gcc -Wall -c --coverage $(files)
	gcc -Wall -c $(INCL_DIRS) -DUNITY_FIXTURES mocks/MockState.c mocks/MockSymbol.c mocks/MockGenList.c
	gcc -Wall -c $(qcc) # QuickCheck va separado para que cobertura no lo considere
	gcc -Wall --coverage -o $(unity_tests) -DUNITY_FIXTURES $(INC_DIRS) $(SRC_FILES)
	gcc -Wall --coverage -o Symbol-qcc Symbol.o quickcheck4c.o test/Symbol-qcc.c
	gcc -Wall --coverage -o State-qcc State.o quickcheck4c.o test/State-qcc.c
	gcc -Wall --coverage -o GenList-qcc GenList.o quickcheck4c.o test/GenList-qcc.c
	@#gcc -Wall --coverage -o Transition-test Transition.o test/Transition-test.c
	@#gcc -Wall --coverage -o DFA-test DFA.o test/DFA-test.c
	@echo "Compiling source files... Done."

tests: cunit
	@echo "Running tests..."
	@./$(unity_tests) -v
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
	rm -rf *~ core $(output) $(unity_tests) *-qcc *-test *.tst doc/cppcheck.xml doc/coverage *.gcda *.gcno *.o mocks/* mocks/
	@echo "Cleaning directories... Done."

