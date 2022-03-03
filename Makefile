all: prog1 prog2
prog1: prog1.cpp
	g++ prog1.cpp -o prog1
prog2: prog2.cpp
	g++ prog2.cpp -o prog2