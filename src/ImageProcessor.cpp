// ------------------
// ImageProcessor.c++
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(std::vector<std::vector<char>>& board, cv::Mat& sudokuImage) : _board(board), _sudokuImage(sudokuImage) {
    cv::Size size = _sudokuImage.size();

    _cellWidth = size.width / BOARDSIZE;
    _cellHeight = size.height / BOARDSIZE;

    _cellOffsetWidth = _cellWidth / 9;
    _cellOffsetHeight = _cellHeight / 9;
}

void ImageProcessor::PopulateBoard() {
    // Initialize a Tesseract instance.
    tesseract::TessBaseAPI tess;
    tess.Init(NULL, "eng");

    // Treat the image as a single text line.
    tess.SetPageSegMode(static_cast<tesseract::PageSegMode>(7));

    // Only recognize numbers.
    tess.SetVariable("tessedit_char_whitelist", "0123456789");

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            // Definds the region of interest. Get each cell from the original sudoku image.
            cv::Rect rect = cv::Rect(_cellWidth * j + _cellOffsetWidth, _cellHeight * i + _cellOffsetHeight, _cellWidth - 2 * _cellOffsetWidth, _cellHeight - 2 * _cellOffsetHeight);
            cv::Mat block = cv::Mat(_sudokuImage, rect);

            // Apply thresholding to get binary image.
            cv::Mat binary(block.size(), block.type());
            cv::threshold(block, binary, 100, 255, cv::THRESH_BINARY);

            // Use Tesseract to read number from each cell.
            tess.SetImage((uchar*)binary.data, binary.size().width, binary.size().height, binary.channels(), binary.step1());
            tess.Recognize(0);
            std::string text = tess.GetUTF8Text();

            // Remove whitespaces from read text.
            text.erase(remove_if(text.begin(), text.end(), isspace), text.end());

            // Populate the board.
            if(text == "") {
                _board[i][j] = '.';
                _emptyX.push_back(i);
                _emptyY.push_back(j);
            } else {
                _board[i][j] = text[0];
            }
        }
    } 
}

void ImageProcessor::RecordAnswers() {
    // Number of empty cells to record.
    int numToRecord = _emptyX.size();

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            for(int k = 0; k < numToRecord; ++k) {
                if(_emptyX[k] == i && _emptyY[k] == j) {
                    std::string c = std::string(1, _board[i][j]);

                    // Record the answer in the right cell.
                    putText(_sudokuImage, c, cvPoint(_cellWidth * j + 2 * _cellOffsetWidth, _cellHeight * (i + 1) - 2 * _cellOffsetHeight), cv::FONT_HERSHEY_SIMPLEX, 2, cvScalar(70, 55, 192, 0), 1, CV_AA);
                }
            }
        }
    }
}
