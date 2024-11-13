all: hello
		hello1

hello: main.o FileInputer.o FileOut.o mumuCompiler.o
	g++ main.o FileInputer.o FileOut.o mumuCompiler.o -o hello1

main.o: main.cpp
	g++ -c main.cpp

FileInputer.o: FileInputer.cpp
	g++ -c FileInputer.cpp

FileOut.o: FileOut.cpp
	g++ -c FileOut.cpp

mumuCompiler.o: mumuCompiler.cpp
	g++ -c mumuCompiler.cpp

clean:
	rm -rf *.o hello