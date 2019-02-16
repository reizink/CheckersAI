a.out: checkers.o space.o game.o main.o
	g++ checkers.o space.o game.o main.o
game.o: game.cc game.h
	g++ -c game.cc
checkers.o: checkers.cc game.h checkers.h space.h colors.h
	g++ -c checkers.cc
space.o: space.cc game.h space.h colors.h checkers.h
	g++ -c space.cc
main.o: main.cc
	g++ -c main.cc
