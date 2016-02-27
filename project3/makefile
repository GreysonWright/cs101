project3:	project3.o SparseMatrix.o
	g++ -Wall -std=c++11 -o project3 project3.o SparseMatrix.o

SparseMatrix:	SparseMatrix.h SparseMatrix.cpp
	g++ -Wall -std=c++11 -c SparseMatrix.cpp

project3.o:	project3.cpp SparseMatrix.h SparseMatrix.cpp
	g++ -Wall -std=c++11 -c project3.cpp

clean:	
	rm -f *.o project3
