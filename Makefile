all:
	g++ -std=c++11 main.cpp `pkg-config --libs --cflags opencv` -o p