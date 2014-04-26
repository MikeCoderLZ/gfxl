all: classTests.exe

classTests.exe: classTests.o moduleA.o moduleB.o
	g++ classTests.o moduleA.o moduleB.o -o classTest.exe

classTests.o: classTests.cpp moduleA.hpp moduleB.hpp
	g++ -c classTests.cpp -o classTests.o
	
moduleA.o: moduleA.cpp classA.hpp
	g++ -c moduleA.cpp -o moduleA.o
	
moduleB.o: moduleB.cpp classA.hpp
	g++ -c moduleB.cpp -o moduleB.o