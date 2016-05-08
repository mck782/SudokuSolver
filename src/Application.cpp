// ------------------
// Application.c++
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

#include "SudokuSolver.h"
#include "ImageProcessor.h"

#include <iostream>

const char* windowName = "SudokuSolver";

int main(int argc, char* argv[]) {
	// Initialize a 2D vector that represents the given sudoku board.
	std::vector<std::vector<char>> board(BOARDSIZE, std::vector<char>(BOARDSIZE));

	// Read the sudoku image.
	cv::namedWindow(windowName, cv::WINDOW_NORMAL);
	char* sudokuFile; 
	if(argc == 2) {
		sudokuFile = argv[1];
	} else {
		// throw
	}
	cv::Mat sudokuImage = cv::imread(sudokuFile, CV_LOAD_IMAGE_GRAYSCALE);

	// Populate the board using the given image.
	ImageProcessor imageProcessor(board, sudokuImage);
	imageProcessor.Preprocessing();
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
