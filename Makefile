main: main.o 
	g++ main.o -o main

main.o: main.cpp
	g++ -Wall -c main.cpp

clean:
	rm  main.o main
