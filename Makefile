main : tree.o main.o
	g++ -o main tree.o main.o
tree.o : Tree.cpp Tree.h
	g++ Tree.cpp
main.o : main.cpp
	g++  main.cpp
