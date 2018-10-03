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
	rm *.o P1.out *.gch *.p1 *.lst

all: Project1.o SetLimits.o LexicalAnalyzer.o SyntacticalAnalyzer.o 

exec: P1.out

run: 
	./P1.out P1-0.ss

p1: all exec run

submit : Project1.cpp LexicalAnalyzer.h LexicalAnalyzer.cpp SyntacticalAnalyzer.h SyntacticalAnalyzer.cpp makefile README.txt
	rm -rf yourlastnameP1
	mkdir yourlastnameP1
	cp Project1.cpp yourlastnameP1
	cp LexicalAnalyzer.h yourlastnameP1
	cp LexicalAnalyzer.cpp yourlastnameP1
	cp SyntacticalAnalyzer.h yourlastnameP1
	cp SyntacticalAnalyzer.cpp yourlastnameP1
	cp makefile yourlastnameP1
	cp README.txt yourlastnameP1
	tar cfvz yourlastnameP1.tgz yourlastnameP1
	cp yourlastnameP1.tgz ~tiawatts/cs460drop
