// ------------------
// Application.c++
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

#include "SudokuSolver.h"
#include "ImageProcessor.h"

const char* windowName = "SudokuSolver";
const char* sudokuFile = "../data/sudoku.jpg";

int main() {
	// Initialize a 2D vector that represents the given sudoku board.
	std::vector<std::vector<char>> board(BOARDSIZE, std::vector<char>(BOARDSIZE));

	// Read the sudoku image.
	cv::namedWindow(windowName, 1);
	cv::Mat sudokuImage = cv::imread(sudokuFile, 1);

	// Populate the board using the given image.
	ImageProcessor imageProcessor(board, sudokuImage);
	imageProcessor.PopulateBoard();

	// Solve the board.
	SudokuSolver sudokuSolver(board);
	sudokuSolver.Solve();

	// Record the answer to the image.
	imageProcessor.RecordAnswers();

	// Display the solved imaged.
	cv::imshow(windowName, sudokuImage);
	cv::waitKey();

    return 0;
}
