project1:   main.o
	g++ -Wall -std=c++11 -o project1 main.o

main.o:	main.cpp
	g++ -c -Wall -std=c++11 main.cpp

clean:	
	rm -f *.o project1

test:	project1
	cat test.dat | ./project1
