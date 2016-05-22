// ------------------
// ImageProcessor.c++
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

#include "ImageProcessor.h"
#include <iostream>

ImageProcessor::ImageProcessor(std::vector<std::vector<char>>& board, cv::Mat& sudokuImage) : _board(board), _sudokuImage(sudokuImage) {
    cv::resize(_sudokuImage, _sudokuImage, cv::Size(3500, 3500));
    cv::Size size = _sudokuImage.size();

    _cellWidth = size.width / BOARDSIZE;
    _cellHeight = size.height / BOARDSIZE;

    _cellOffsetWidth = _cellWidth / 9;
    _cellOffsetHeight = _cellHeight / 9;

    // Chooses how we erode and dilate
    _morphologyElement = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3, 3));
}

void ImageProcessor::Preprocessing() {
    // Make a copy of the original sudoku image in order to preprocess.
    cv::Mat preprocess = _sudokuImage.clone();

    // Apply adaptive threshold to filter out noise.
    cv::adaptiveThreshold(preprocess, preprocess, 255, cv::ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY_INV, 355, 0);

    // Convert the image to YCrCb.
    cv::cvtColor(preprocess, preprocess, CV_GRAY2BGR);
    cv::cvtColor(preprocess, preprocess, CV_BGR2YCrCb);

    // Apply channel threshold.
    SplitThreshold(preprocess);

    // Convert the image back to grayscale.
    cv::cvtColor(preprocess, preprocess, CV_YCrCb2BGR);
    cv::cvtColor(preprocess, preprocess, CV_BGR2GRAY);

    // Apply more threshold.
    cv::GaussianBlur(preprocess, preprocess, cv::Size(7,7), 1.8, 1.8);
    cv::threshold(preprocess, preprocess, 120, 255, cv::THRESH_BINARY_INV);

    // Find the largest connect component and warp perspective.
    std::vector<cv::Point> contour;
    bool found = FindLargestCC(preprocess, contour);
    if(found) {
        WarpBoard(preprocess, contour);
    }

    // Apply more threshold.
    cv::GaussianBlur(_sudokuImage, _sudokuImage, cv::Size(7,7), 1.8, 1.8);
    // cv::adaptiveThreshold(_sudokuImage, _sudokuImage, 255,CV_ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 25, 2);

    int threshold_val = 120;
    GetBrightness(_sudokuImage, threshold_val);

    // int threshold_val = static_cast<int>(brightness * );

    cv::threshold(_sudokuImage, _sudokuImage, threshold_val, 255, cv::THRESH_BINARY); // 120, 255

    // Convert the image back to RGB.
    cv::cvtColor(_sudokuImage, _sudokuImage, CV_GRAY2BGR);
}

void ImageProcessor::PopulateBoard() {
    // Initialize a Tesseract instance.
    tesseract::TessBaseAPI tess;

    for(int i = 0; i < BOARDSIZE; ++i) {
        for(int j = 0; j < BOARDSIZE; ++j) {
            tess.Init(NULL, "eng");

            // Treat the image as a single text line.
            // TODO : Inspect the impact of using 7 instead of 10.
            tess.SetPageSegMode(static_cast<tesseract::PageSegMode>(7));

            // Only recognize numbers.
            tess.SetVariable("tessedit_char_whitelist", "123456789");

            // Definds the region of interest. Get each cell from the original sudoku image.
            cv::Rect rect = cv::Rect(_cellWidth * j + _cellOffsetWidth, _cellHeight * i + _cellOffsetHeight, _cellWidth - 2 * _cellOffsetWidth, _cellHeight - 2 * _cellOffsetHeight);
            cv::Mat block = cv::Mat(_sudokuImage, rect);

            // Apply thresholding to get binary image.
            cv::Mat binary(block.size(), block.type());
            cv::threshold(block, binary, 100, 255, cv::THRESH_BINARY);

            // // Filter out noise by Gaussian pyramid methods.
            // cv::Mat pyrDown, pyrUp;
            // cv::pyrDown(binary, pyrDown, cv::Size(binary.cols/2, binary.rows/2));
            // cv::pyrUp(pyrDown, pyrUp, binary.size());

            // // Make the cell 4 times bigger by making border.
            // int borderRows = (int)(pyrUp.rows * 2);
            // int borderCols = (int)(pyrUp.cols * 2);
            // cv::Mat border;
            // cv::copyMakeBorder(pyrUp, border, borderRows, borderRows, borderCols, borderCols, cv::BORDER_CONSTANT, cv::Scalar(255, 255, 255) );

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
    for(int i = 0; i < BOARDSIZE; ++i){
        for(int j = 0; j < BOARDSIZE; ++j){
            std::cout<< _board[i][j]; 
        }
        std::cout<<std::endl;
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
                    putText(_sudokuImage, c, cvPoint(_cellWidth * j + 2 * _cellOffsetWidth, _cellHeight * (i + 1) - 2 * _cellOffsetHeight), cv::FONT_HERSHEY_SIMPLEX, 10, cv::Scalar(0, 0, 255), 2, CV_AA);
                
                    // putText(_sudokuImage, c, cvPoint(_cellWidth * j + 2 * _cellOffsetWidth, _cellHeight * (i + 1) - 2 * _cellOffsetHeight), cv::FONT_HERSHEY_SIMPLEX, 10, cv::Scalar(0, 0, 255), 3, CV_AA);
                }
            }
        }
    }
}

void ImageProcessor::SplitThreshold(cv::Mat& image) {
    // We assume that the image is already converted to YCrCb format.
    cv::Mat channels[3];
    cv::split(image, channels);

    for (int i = 0; i < 3; i++) {
        // Applies a threshold using Otsu's method.
        cv::threshold(channels[i], channels[i], 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);

        // Runs pixel erosion and dilation for three iterations.
        cv::morphologyEx(channels[i], channels[i], cv::MORPH_OPEN, _morphologyElement, cv::Point(-1, -1), 3);
    }

    // Merge the channels back together.
    cv::merge(channels, 3, image);

    // Again, runs pixel erosion and dilation for three iterations.
    cv::morphologyEx(image, image, cv::MORPH_OPEN, _morphologyElement, cv::Point(-1, -1), 3);
}

bool ImageProcessor::FindLargestCC(cv::Mat& image, std::vector<cv::Point>& contour) {
    // Use Canny algorithm to detect endges
    cv::Mat canny;
    cv::Canny(image, canny, 100, 300, 3);

    // Find all contours/connected components.
    std::vector<std::vector<cv::Point>> contours;
    cv::findContours(canny, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

    // Find the largest connected component.
    cv::Mat mask = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);
    std::vector<double> areas(contours.size());
    for(int i = 0; i < (int)contours.size(); i++) {
        areas[i] = cv::contourArea(cv::Mat(contours[i]));
    }
    double max;
    cv::Point maxPosition;
    cv::minMaxLoc(cv::Mat(areas), 0, &max, 0, &maxPosition);
    cv::drawContours(mask, contours, maxPosition.y, cv::Scalar(1), CV_FILLED);

    // Copy the largest connect component into the new image.
    cv::Mat crop(_sudokuImage.rows, _sudokuImage.cols, CV_8UC3);
    image.copyTo(crop, mask);

    // Find the square board.
    cv::approxPolyDP(cv::Mat(contours[maxPosition.y]), contour, cv::arcLength(cv::Mat(contours[maxPosition.y]), true)*0.02, true);

    // Return true if the found largest connect component is larget enough.
    // return cv::contourArea(cv::Mat(contours[maxPosition.y])) > 3500 * 3500 / 3;
    return cv::contourArea(cv::Mat(contours[maxPosition.y])) > _cellWidth * _cellHeight * 27;
}

bool CompareCoordinateSum(cv::Point a, cv::Point b) {
    return a.x + a.y < b.x + b.y;
}

bool CompareCoordinateDiff(cv::Point a, cv::Point b) {
    return a.x - a.y < b.x - b.y;
}

void ImageProcessor::WarpBoard(cv::Mat& image, const std::vector<cv::Point>& contour) {
        cv::Point2f input[4];
        input[0] = *std::min_element(contour.begin(), contour.end(), CompareCoordinateSum);
        input[1] = *std::max_element(contour.begin(), contour.end(), CompareCoordinateDiff);
        input[2] = *std::max_element(contour.begin(), contour.end(), CompareCoordinateSum);
        input[3] = *std::min_element(contour.begin(), contour.end(), CompareCoordinateDiff);

        size_t warpOffsetWidth = _cellOffsetWidth / 7;
        size_t warpOffsetHeight = _cellOffsetHeight / 7;

        input[0] = cv::Point2f(input[0].x + warpOffsetWidth, input[0].y + warpOffsetHeight);
        input[1] = cv::Point2f(input[1].x - warpOffsetWidth, input[1].y + warpOffsetHeight);
        input[2] = cv::Point2f(input[2].x - warpOffsetWidth, input[2].y - warpOffsetHeight);
        input[3] = cv::Point2f(input[3].x + warpOffsetWidth, input[3].y - warpOffsetHeight);

        cv::Point2f output[4];
        output[0] = cv::Point2f(0, 0);
        output[1] = cv::Point2f(image.cols - 1, 0);
        output[2] = cv::Point2f(image.cols - 1, image.rows - 1);
        output[3] = cv::Point2f(0, image.rows - 1);

        cv::Mat transform = cv::getPerspectiveTransform(input, output);
        cv::warpPerspective(_sudokuImage, _sudokuImage, transform, _sudokuImage.size());
}

// get brightness 0.0 to 1.0 
void ImageProcessor::GetBrightness(const cv::Mat& img, int& threshold_val) {
    cv::Mat temp, color[3], lum;
    temp = img;

    cv::split(temp, color);

    color[0] = color[0] * 0.299;
    color[1] = color[1] * 0.587;
    color[2] = color[2] * 0.114;


    lum = color[0] + color [1] + color[2];

    cv::Scalar summ = sum(lum);

    double brightness = summ[0]/((pow(2,8)-1)*img.rows * img.cols) * 2;
    threshold_val = static_cast<int>((brightness * 380) - 40);
    threshold_val = (threshold_val / 10) * 10;
 }
