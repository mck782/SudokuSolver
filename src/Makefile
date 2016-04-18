PKG_CONFIG=`pkg-config --cflags --libs opencv`
FLAGS=-pedantic -std=c++11 -Wall

cc = g++

all:

SudokuSolver: Application.cpp SudokuSolver.h SudokuSolver.cpp ImageProcessor.h ImageProcessor.cpp
	$(cc) ${FLAGS} Application.cpp SudokuSolver.cpp ImageProcessor.cpp -o SudokuSolver ${PKG_CONFIG}

clean:
	-rm -f SudokuSolver