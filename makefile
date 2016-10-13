# DLP - Practice 1
# Java Makefile
#
# Xoan Andreu Barro Torres (andreu.barro)
# Manoel Anton Folgueira Hernandez (manoel.folgueira)
# Uxia Ponte Villaverde (uxia.ponte.villaverde)

output = out
files = Symbol.c State.c GenList.c Alphabet.c Transition.c DFA.c main.c
dfa_file = example.dfa

default:
	gcc -o $(output) $(files)

run:
	./$(output) $(dfa_file)

all:
	make
	make run

clean:
	rm ./(output)
