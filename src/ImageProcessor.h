// ------------------
// ImageProcessor.h
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

// Ignore GCC diagonostic.
#pragma GCC diagnostic ignored "-Wpragmas"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <tesseract/baseapi.h>
#include <vector>
#include <string>

#define BOARDSIZE 9

/**
 * Class that manipulates the given image.
 */
class ImageProcessor {
private:
	std::vector<std::vector<char>>& _board;
	std::vector<int> _emptyX;
	std::vector<int> _emptyY;
	cv::Mat& _sudokuImage;

	size_t _cellWidth;
	size_t _cellHeight;
	size_t _cellOffsetWidth;
	size_t _cellOffsetHeight;

public:
	/**
     * Constructor for ImageProcessor class.
     * @param std::vector<std::vector<char>>& reference to the sudoku board.
     * @param cv::Mat& reference to OpenCV Mat representation of the sudoku image.
     */
	ImageProcessor(std::vector<std::vector<char>>&, cv::Mat&);

	/**
     * Populate the board with the given image.
     */
	void PopulateBoard();

	/**
     * Record the answers to the image.
     */
	void RecordAnswers();
};
