#include "ImageProcessor.h"

ImageProcessor::ImageProcessor(vector<vector<char>>& board, Mat& sudokuImage) : _board(board), _sudokuImage(sudokuImage) 
{}

// Find cosine the angle between two vectors.
// dot product / product of lengths
static double angle(const Point& pt1, const Point& pt2, const Point& pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void ImageProcessor::PopulateBoard() {
    int thresh = 500, N = 11;
	vector<vector<Point>> squares;
	Mat pyr, timg, gray0(_sudokuImage.size(), CV_8U), gray;

    pyrDown(_sudokuImage, pyr, Size(_sudokuImage.cols/2, _sudokuImage.rows/2));
    pyrUp(pyr, timg, _sudokuImage.size());
    vector<vector<Point> > contours;

    for(int c = 0; c < 3; c++ ) {
        int ch[] = {c, 0};
        mixChannels(&timg, 1, &gray0, 1, ch, 1);

        for(int l = 0; l < N; l++ ) {
            if( l == 0 ) {
                Canny(gray0, gray, 0, thresh, 5);
                dilate(gray, gray, Mat(), Point(-1,-1));
            } else {
                gray = gray0 >= (l+1)*255/N;
            }

            findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
            vector<Point> approx;

            for(size_t i = 0; i < contours.size(); i++ ) {
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                if(approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx))) {
                    double maxCosine = 0;

                    for(int j = 2; j < 5; j++) {
                        double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                        maxCosine = MAX(maxCosine, cosine);
                    }

                    if(maxCosine < 0.3)
                        squares.push_back(approx);
                }
            }
        }
    }

    for(size_t i = 0; i < squares.size(); i++) {
        const Point* p = &squares[i][0];
        int n = (int)squares[i].size();
        polylines(_sudokuImage, &p, &n, 1, true, Scalar(0,255,0), 3, LINE_AA);
    }
}