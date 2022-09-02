programa: main.o
	g++ main.o -o programa

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm *.o programa