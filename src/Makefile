PKG_CONFIG=`pkg-config --cflags --libs opencv tesseract`
FLAGS=-pedantic -std=c++11 -Wall

cc = g++

all:

SudokuSolver: Application.cpp SudokuSolver.h SudokuSolver.cpp ImageProcessor.h ImageProcessor.cpp
	$(cc) ${FLAGS} Application.cpp SudokuSolver.cpp ImageProcessor.cpp -o SudokuSolver ${PKG_CONFIG} 

dev: DevRun.cpp SudokuSolver.h SudokuSolver.cpp ImageProcessor.h ImageProcessor.cpp
	$(cc) ${FLAGS} DevRun.cpp SudokuSolver.cpp ImageProcessor.cpp -o SudokuSolver ${PKG_CONFIG} 

test: TestSudokuSolver.cpp SudokuSolver.h SudokuSolver.cpp ImageProcessor.h ImageProcessor.cpp
	$(cc) ${FLAGS} TestSudokuSolver.cpp SudokuSolver.cpp ImageProcessor.cpp -o TestSudokuSolver ${PKG_CONFIG} 

clean:
	-rm -f SudokuSolver
