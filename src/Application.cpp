#include "SudokuSolver.h"
#include "ImageProcessor.h"

#include <iostream>

//using namespace cv;
//using namespace std;

const char* windowName = "SudokuSolver";
const char* sudokuFile = "../data/sudoku.jpg";

int main() {
	std::vector<std::vector<char>> sudoku;
	std::vector<char> r1 = {'5', '3', '.', '.', '7', '.', '.', '.', '.'};
	sudoku.push_back(r1);
	std::vector<char> r2 = {'6', '.', '.', '1', '9', '5', '.', '.', '.'};
	sudoku.push_back(r2);
	std::vector<char> r3 = {'.', '9', '8', '.', '.', '.', '.', '6', '.'};
	sudoku.push_back(r3);
	std::vector<char> r4 = {'8', '.', '.', '.', '6', '.', '.', '.', '3'};
	sudoku.push_back(r4);
	std::vector<char> r5 = {'4', '.', '.', '8', '.', '3', '.', '.', '1'};
	sudoku.push_back(r5);
	std::vector<char> r6 = {'7', '.', '.', '.', '2', '.', '.', '.', '6'};
	sudoku.push_back(r6);
	std::vector<char> r7 = {'.', '6', '.', '.', '.', '.', '2', '8', '.'};
	sudoku.push_back(r7);
	std::vector<char> r8 = {'.', '.', '.', '4', '1', '9', '.', '.', '5'};
	sudoku.push_back(r8);
	std::vector<char> r9 = {'.', '.', '.', '.', '8', '.', '.', '7', '9'};
	sudoku.push_back(r9);

	//cv::namedWindow(windowName, 1);
	cv::Mat sudokuImage = cv::imread(sudokuFile, 1);

	ImageProcessor imageProcessor(sudoku, sudokuImage);
	imageProcessor.PopulateBoard();

	SudokuSolver solver(sudoku);
	solver.Solve();

	std::cout << std::endl;
	for(int i = 0; i < 9; ++i) {
            for(int j = 0; j < 9; ++j) {
                std::cout << sudoku[i][j] << " ";
            }
            std::cout << std::endl;
        }

	imageProcessor.RecordAnswers();

	cv::imshow(windowName, sudokuImage);
	cv::waitKey();

    return 0;
}
