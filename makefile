final: all exec

p1: all exec run

P1.out : Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o 
	g++ -g -o P1.out Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o 

Project1.o : Project1.cpp SetLimits.h SyntacticalAnalyzer.h
	g++ -g -c Project1.cpp

SetLimits.o : SetLimits.cpp SetLimits.h
	g++ -g -c SetLimits.cpp

LexicalAnalyzer.o : LexicalAnalyzer.cpp LexicalAnalyzer.h transition.hpp
	g++ -g -c LexicalAnalyzer.cpp

SyntacticalAnalyzer.o : SyntacticalAnalyzer.cpp SyntacticalAnalyzer.h LexicalAnalyzer.h
	g++ -g -c SyntacticalAnalyzer.cpp

clean : 
	rm *.o P1.out *.gch *.p1 *.lst *.dbg

all: Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o 

exec: P1.out

run: 
	./P1.out P1-0.ss


submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf TeamdP1
	mkdir TeamdP1
	cp Project1.cpp TeamdP1
	cp LexicalAnalyzer.h TeamdP1
	cp LexicalAnalyzer.cpp TeamdP1
	cp SyntacticalAnalyzer.h TeamdP1
	cp SyntacticalAnalyzer.cpp TeamdP1
	cp makefile TeamdP1
	cp README.txt TeamdP1
	tar cfvz yourlastnameP1.tgz TeamdP1
	cp TeamdP1.tgz ~tiawatts/cs460drop
