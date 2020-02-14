all: run

compile: main.cpp
	g++ main.cpp -std=c++17 -o main

run: compile
	./main < test.in > result.out
