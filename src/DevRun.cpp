// ------------------
// DevRun.c++
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------
//
// *NOTE*
//
// This is the exact copy of `Application.cpp`, except that
// this does not make any use of `imshow` function from OpenCV.
// With Docker container in place, unfortunately, any functions that
// make any use of GTK(something that requires a display) will not work.
// `imshow` function shows an image, thus having this function in the application
// will not allow Docker "compiler" to run.
// Instead, `imwrite` function is used to save the image into a file.
// And the file can be inspected at will.

#include "SudokuSolver.h"
#include "ImageProcessor.h"

const char* windowName = "SudokuSolver";

int main(int argc, char* argv[]) {
	// Initialize a 2D vector that represents the given sudoku board.
	std::vector<std::vector<char>> board(BOARDSIZE, std::vector<char>(BOARDSIZE));

	// Read the sudoku image.
	char* sudokuFile; 
	if(argc == 2) {
		sudokuFile = argv[1];
	} else {
		// throw
	}
	cv::Mat sudokuImage = cv::imread(sudokuFile, 1);

	// Populate the board using the given image.
	ImageProcessor imageProcessor(board, sudokuImage);
	imageProcessor.PopulateBoard();

	// Solve the board.
	SudokuSolver sudokuSolver(board);
	sudokuSolver.Solve();

	// Record the answer to the image.
	imageProcessor.RecordAnswers();

	// Save the solved imaged.
	cv::imwrite("solution.jpg", sudokuImage);

    return 0;
}
