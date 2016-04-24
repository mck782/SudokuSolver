#include "ImageProcessor.h"

#include <iostream>

ImageProcessor::ImageProcessor(vector<vector<char>>& board, Mat& sudokuImage) : _board(board), _sudokuImage(sudokuImage) 
{}

// Find cosine the angle between two vectors.
// dot product / product of lengths
double ImageProcessor::FindCosine(const Point& pt1, const Point& pt2, const Point& pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void ImageProcessor::PopulateBoard() {
    
    int rowSize = _sudokuImage.rows / 9;
    int colSize = _sudokuImage.cols / 9;
    int rowBlockSize, colBlockSize;

    cout << "Approx. size of a square: " << rowSize << ", " << colSize << endl;
    
    for (int i=0; i<9; i++) {
        rowBlockSize = rowSize * i;
        for (int j=0; j<9; j++) {
            colBlockSize = colSize * j;
            string filename = "box" + to_string(i) + to_string(j) + ".jpg";
            Rect box = Rect(rowBlockSize, colBlockSize, rowSize, colSize);
            imwrite(filename, _sudokuImage(box));
        }
    }
}

void ImageProcessor::RecordAnswers() {
    
}
