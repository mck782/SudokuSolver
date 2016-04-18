PKG_CONFIG=`pkg-config --cflags --libs opencv`
FLAGS=-pedantic -std=c++11 -Wall

cc = gcc

all:

SudokuSolver: Application.cpp SudokuSolver.h SudokuSolver.cpp
	$(cc) ${FLAGS} Application.cpp SudokuSolver.cpp -o SudokuSolver ${PKG_CONFIG}

clean:
	-rm -f SudokuSolver