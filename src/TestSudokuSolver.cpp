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
#include <fstream>
#include <string>
 
/*
char sudoku_pic2_answer[81] = {'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.',
								'.','.','.','.','.','.','.','.','.'};
*/

const int NUMBER_OF_SUDOKU = 7;
const int NUMBER_TOTAL = NUMBER_OF_SUDOKU * 81;
int totalWrong = 0;

void testBoard(cv::Mat sudokuImage, std::vector<std::vector<char>> board, std::string sudokuName, char answer[], std::ofstream &OF);
// const char* windowName = "SudokuSolver";

int main(int argc, char* argv[]) {
	
	std::ofstream testResult;
	testResult.open ("testResult.txt");
	testResult << "  << RESULT >>\n";
	

	// ANSWERS

	char sudoku_answer[81] = {'.','1','.','4','2','.','.','.','5',
			 				  '.','.','2','.','7','1','.','3','9',
							  '.','.','.','.','.','.','.','4','.',
							  '2','.','7','1','.','.','.','.','6',
							  '.','.','.','.','4','.','.','.','.',
							  '6','.','.','.','.','7','4','.','3',
							  '.','7','.','.','.','.','.','.','.',
							  '1','2','.','7','3','.','5','.','.',
							  '3','.','.','.','8','2','.','7','.'};

	char sudoku_img_answer[81] = {'6','1','.','.','.','.','.','.','.',
							      '.','4','8','.','5','3','1','.','2',
							      '.','.','3','.','8','.','.','4','5',
							      '4','.','.','.','9','.','5','.','6',
							      '.','5','7','.','3','.','2','.','.',
							      '3','.','.','5','.','8','.','1','.',
							      '.','3','9','.','.','.','6','2','1',
							      '7','2','.','.','6','5','3','.','.',
							      '8','.','4','3','.','2','.','5','9'};

	char sudoku_img2_answer[81] = {'3','.','2','.','.','.','6','7','.',
								   '.','8','.','.','.','.','.','.','.',
								   '7','.','.','3','1','6','.','.','.',
								   '.','.','8','.','.','.','.','5','.',
								   '9','.','.','.','3','.','8','.','.',
								   '.','.','5','.','.','8','.','1','.',
								   '4','5','.','6','.','1','.','8','.',
								   '.','.','.','.','.','.','2','.','5',
								   '8','.','.','.','5','.','.','.','.'};

	char sudoku_pic_answer[81] = {'8','.','.','.','1','.','.','.','9',
								  '.','5','.','8','.','7','.','1','.',
								  '.','.','4','.','9','.','7','.','.',
								  '.','6','.','7','.','1','.','2','.',
								  '5','.','8','.','6','.','1','.','7',
								  '.','1','.','5','.','2','.','9','.',
								  '.','.','7','.','4','.','6','.','.',
								  '.','8','.','3','.','9','.','4','.',
								  '3','.','.','.','5','.','.','.','8'};

	char sudoku_pic2_answer[81] = {'.','.','.','6','.','4','7','.','.',
								   '7','.','6','.','.','.','.','.','9',
								   '.','.','.','.','.','5','.','8','.',
								   '.','7','.','.','2','.','.','9','3',
								   '8','.','.','.','.','.','.','.','5',
								   '4','3','.','.','1','.','.','7','.',
								   '.','5','.','2','.','.','.','.','.',
								   '3','.','.','.','.','.','2','.','8',
								   '.','.','2','3','.','1','.','.','.'};

	char sudoku_pic3_answer[81] = {'5','.','.','.','4','.','.','.','.',
								   '.','.','2','.','9','.','.','8','1',
								   '.','.','.','.','.','1','.','.','.',
								   '.','.','.','.','.','.','1','3','.',
								   '3','8','.','.','.','9','.','.','4',
								   '.','.','.','1','.','.','.','2','6',
								   '4','5','.','.','.','.','6','.','9',
								   '.','.','.','9','.','.','.','.','2',
								   '9','.','.','.','7','8','.','.','.'};

	char sudoku_pic4_answer[81] = {'8','.','.','6','.','3','.','.','1',
								   '.','5','7','4','.','1','6','3','.',
								   '.','.','.','.','.','.','.','.','.',
								   '.','.','6','1','.','9','8','.','.',
								   '4','.','.','.','.','.','.','.','7',
								   '.','.','1','8','.','5','4','.','.',
								   '.','.','.','.','.','.','.','.','.',
								   '.','7','2','5','.','4','3','1','.',
								   '9','.','.','3','.','2','.','.','4'};

	char sudoku_self_answer[81] = {'.','.','.','.','.','.','3','2','.',
								   '6','.','4','.','.','.','.','.','9',
								   '.','.','.','8','9','1','5','.','.',
								   '1','.','3','.','2','.','.','.','.',
								   '.','6','.','4','.','9','.','1','.',
								   '.','.','.','.','5','.','8','.','2',
								   '.','.','8','5','1','7','.','.','.',
								   '3','.','.','.','.','.','9','.','8',
								   '.','7','6','.','.','.','.','.','.'};

	char sudoku_self2_answer[81] = {'2','7','.','8','.','.','6','.','.',
									'.','.','8','.','.','.','.','3','9',
									'.','.','.','2','4','.','.','.','.',
									'6','9','4','.','3','.','.','.','.',
									'.','.','.','6','.','7','.','.','.',
									'.','.','.','.','2','.','8','5','6',
									'.','.','.','.','9','6','.','.','2',
									'4','2','.','.','.','.','9','.','.',
									'.','.','5','.','.','2','.','4','8'};

	// Initialize a 2D vector that represents the given sudoku board.
	std::vector<std::vector<char>> board(BOARDSIZE, std::vector<char>(BOARDSIZE));


	// testing "../data/sudoku.jpg"
	cv::Mat sudokuImage = cv::imread("../data/sudoku.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku.jpg", sudoku_answer, testResult);

	// testing "../data/sudoku_img.jpg"
 	sudokuImage = cv::imread("../data/sudoku_img.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_img.jpg", sudoku_img_answer, testResult);

	// testing "../data/sudoku_img2.jpg"
	sudokuImage = cv::imread("../data/sudoku_img2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_img2.jpg", sudoku_img2_answer, testResult);

	// testing "../data/sudoku_pic.jpg"
	sudokuImage = cv::imread("../data/sudoku_pic.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_pic.jpg", sudoku_pic_answer, testResult);

	// testing "../data/sudoku_pic2.jpg"
	sudokuImage = cv::imread("../data/sudoku_pic2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_pic2.jpg", sudoku_pic2_answer, testResult);

	// testing "../data/sudoku_pic3.jpg"
	sudokuImage = cv::imread("../data/sudoku_pic3.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_pic3.jpg", sudoku_pic3_answer, testResult);

	// testing "../data/sudoku_pic4.jpg"
	sudokuImage = cv::imread("../data/sudoku_pic4.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_pic4.jpg", sudoku_pic4_answer, testResult);

	// testing "../data/sudoku_self.jpg"
	sudokuImage = cv::imread("../data/sudoku_self.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_self.jpg", sudoku_self_answer, testResult);

	// testing "../data/sudoku_self2.jpg"
	sudokuImage = cv::imread("../data/sudoku_self2.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	testBoard(sudokuImage, board, "sudoku_self2.jpg", sudoku_self2_answer, testResult);



	testResult <<  "RESULT: " << static_cast<int>((static_cast<double>(NUMBER_TOTAL - totalWrong) / static_cast<double>(NUMBER_TOTAL)) * 100 ) << "percent of numbers are correct\n";
    
	testResult.close();

    return 0;
}

void testBoard(cv::Mat sudokuImage, std::vector<std::vector<char>> board, std::string sudokuName, char answer[], std::ofstream &OF){
	// Populate the board using the given image.
	ImageProcessor imageProcessor(board, sudokuImage);
	imageProcessor.Preprocessing();
	imageProcessor.PopulateBoard();

	OF << "---- Name: " << sudokuName << " ----\n";

	int wrongCount = 0 ;
	for(int i = 0; i < 9; ++i){
        for(int j = 0; j < 9; ++j){
            // std::cout<< board[i][j]; 
            if(answer[i*9 + j] != board[i][j]){
            	wrongCount++;
            	OF << "(row: " << i << ", col: " << j << ") has value: " << board[i][j] << ", expected: " << answer[i*9 + j] << "\n"; 
            }
        }
    }
    OF <<  static_cast<int>((static_cast<double>(81-wrongCount) / static_cast<double>(81)) * 100 )<< "percent of numbers of this sudoku are correct\n";
    totalWrong += wrongCount;
}
