#include "SudokuSolver.h"
#include "ImageProcessor.h"

#include <iostream>

using namespace cv;
using namespace std;

const char* windowName = "SudokuSolver";
const char* sudokuFile = "../data/sudoku.jpg";

int main() {
	vector<vector<char>> sudoku;
	vector<char> r1 = {'5', '3', '.', '.', '7', '.', '.', '.', '.'};
	sudoku.push_back(r1);
	vector<char> r2 = {'6', '.', '.', '1', '9', '5', '.', '.', '.'};
	sudoku.push_back(r2);
	vector<char> r3 = {'.', '9', '8', '.', '.', '.', '.', '6', '.'};
	sudoku.push_back(r3);
	vector<char> r4 = {'8', '.', '.', '.', '6', '.', '.', '.', '3'};
	sudoku.push_back(r4);
	vector<char> r5 = {'4', '.', '.', '8', '.', '3', '.', '.', '1'};
	sudoku.push_back(r5);
	vector<char> r6 = {'7', '.', '.', '.', '2', '.', '.', '.', '6'};
	sudoku.push_back(r6);
	vector<char> r7 = {'.', '6', '.', '.', '.', '.', '2', '8', '.'};
	sudoku.push_back(r7);
	vector<char> r8 = {'.', '.', '.', '4', '1', '9', '.', '.', '5'};
	sudoku.push_back(r8);
	vector<char> r9 = {'.', '.', '.', '.', '8', '.', '.', '7', '9'};
	sudoku.push_back(r9);

	SudokuSolver solver(sudoku);

	solver.Solve();

	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9 ; j++) {
			cout << sudoku[i][j] << " ";
		}
		cout << endl;
	}

	//namedWindow(windowName, 1);
	//Mat sudokuImage = imread(sudokuFile, 1);
	//imshow(windowName, sudokuImage);
	//waitKey();

    return 0;
}