all: hello
		hello1

hello: main.o FileInProc.o stack_for_comp.o Implementer.o
	g++ main.o FileInProc.o stack_for_comp.o Implementer.o -o hello1

main.o: main.cpp
	g++ -c main.cpp

FileInProc.o: FileInProc.cpp
	g++ -c FileInProc.cpp

stack_for_comp.o: stack_for_comp.cpp
	g++ -c stack_for_comp.cpp

Implementer.o: Implementer.cpp
	g++ -c Implementer.cpp
	
clean:
	rm -rf *.o hello