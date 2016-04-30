#include "ImageProcessor.h"

//#include <iostream>

ImageProcessor::ImageProcessor(std::vector<std::vector<char>>& board, cv::Mat& sudokuImage) : _board(board), _sudokuImage(sudokuImage) 
{}

// Find cosine the angle between two vectors.
// dot product / product of lengths
double ImageProcessor::FindCosine(const cv::Point& pt1, const cv::Point& pt2, const cv::Point& pt0) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void ImageProcessor::PopulateBoard() {
    // Divide up the image into 81 squares.
    cv::Size size = _sudokuImage.size();

    size_t imageWidth = size.width;
    size_t imageHeight = size.height;

    size_t offsetWidth = imageWidth / 9;
    size_t offsetHeight = imageHeight / 9;

    size_t a = offsetWidth / 9;
    size_t b = offsetHeight / 9;

    tesseract::TessBaseAPI myOCR;
    if (myOCR.Init("/Users/mikkel/Desktop/tessdata/", "eng")) {
        fprintf(stderr, "Could not initialize tesseract.\n");
        exit(1);
    }

    std::cout << size.width << " " << size.height << std::endl;

    tesseract::PageSegMode pagesegmode = static_cast<tesseract::PageSegMode>(7); // treat the image as a single text line
    myOCR.SetPageSegMode(pagesegmode);
    myOCR.SetVariable("tessedit_char_whitelist", "0123456789");


    myOCR.SetImage((uchar*)_sudokuImage.data, size.width, size.height, _sudokuImage.channels(), _sudokuImage.step1());
    myOCR.Recognize(0);
    const char *text1 = myOCR.GetUTF8Text();
    std::cout << text1 << std::endl;

    cv::imwrite("../data/shit.png", _sudokuImage);

    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            cv::Rect rect = cv::Rect(offsetWidth * j + a, offsetHeight * i + b, offsetWidth - 2 * a, offsetHeight - 2 * b);
            std::string blockName = "../data/sudoku_" + std::to_string(i) + std::to_string(j) + ".png";
            cv::Mat block = cv::Mat(_sudokuImage, rect);
            //block.convertTo(block, CV_32F);

            //cv::Mat enlarged;
            //cv::resize(block, enlarged, cv::Size(block.rows*2, block.cols*2), cv::INTER_NEAREST);

            //Binary image
            cv::Mat binaryMat(block.size(), block.type());

            //Apply thresholding
            cv::threshold(block, binaryMat, 100, 255, cv::THRESH_BINARY);

            // initialize the output matrix with zeros

            cv::imwrite(blockName, binaryMat);
            /*

            int top = (int) (5*block.rows); 
            int bottom = (int) (5*block.rows);
            int left = (int) (5*block.cols); 
            int right = (int) (5*block.cols);

 
            cv::Mat dst = block;
            cv::copyMakeBorder(block, dst, top, bottom, left, right, 1, cv::Scalar(0, 0, 0) );
            cv::imwrite(blockName, dst);
            */

            myOCR.SetImage((uchar*)binaryMat.data, binaryMat.size().width, binaryMat.size().height, binaryMat.channels(), binaryMat.step1());
            myOCR.Recognize(0);
            const char *text1 = myOCR.GetUTF8Text();
            std::string s = text1;
            s.erase(remove_if(s.begin(), s.end(), isspace), s.end());

            std::cout << blockName << " : " << s << std::endl;
            if(s == "") {
                _board[i][j] = '.';
                _x.push_back(i);
                _y.push_back(j);
            } else {
                _board[i][j] = s[0];
            }
        }
    } 
    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            std::cout << _board[i][j] << " ";
        }
        std::cout << std::endl;
    }

    /*
    int thresh = 500, N = 3;
	std::vector<std::vector<Point>> squares;
	Mat pyr, timg, gray0(_sudokuImage.size(), CV_8U), gray;

    //pyrDown(_sudokuImage, pyr, Size(_sudokuImage.cols/2, _sudokuImage.rows/2));
    //pyrUp(pyr, timg, _sudokuImage.size());
    std::vector<std::vector<Point> > contours;

    for(int c = 0; c < 3; c++) {
        int ch[] = {c, 0};
        mixChannels(&_sudokuImage, 1, &gray0, 1, ch, 1);

        for(int l = 0; l < N; l++) {
            if(l == 0) {
                Canny(gray0, gray, 0, thresh, 7);
                dilate(gray, gray, Mat(), Point(-1,-1));
            } else {
                gray = gray0 >= (l+1)*255/N;
            }

            findContours(gray, contours, RETR_LIST, CHAIN_APPROX_SIMPLE);
            std::vector<Point> approx;

            for(size_t i = 0; i < contours.size(); i++ ) {
                approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                if(approx.size() == 4 &&
                    fabs(contourArea(Mat(approx))) > 1000 &&
                    isContourConvex(Mat(approx))) {
                    double maxCosine = 0;

                    for(int j = 2; j < 5; j++) {
                        double cosine = fabs(FindCosine(approx[j%4], approx[j-2], approx[j-1]));
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
    */
}

void ImageProcessor::RecordAnswers() {
    cv::Size size = _sudokuImage.size();

    size_t imageWidth = size.width;
    size_t imageHeight = size.height;

    size_t offsetWidth = imageWidth / 9;
    size_t offsetHeight = imageHeight / 9;

    size_t a = offsetWidth / 9;
    size_t b = offsetHeight / 9;

    //putText(_sudokuImage, "1", cvPoint(73, 74), cv::FONT_HERSHEY_COMPLEX_SMALL, 3, cvScalar(70, 55, 192, 0), 1, CV_AA);

    for(int i = 0; i < 9; ++i) {
        for(int j = 0; j < 9; ++j) {
            for(int k = 0; k < _x.size(); ++k) {
                if(_x[k] == i && _y[k] == j) {
                    std::string c = std::string(1, _board[i][j]);
                    putText(_sudokuImage, c, cvPoint(offsetWidth * j + 2 * a, offsetHeight * (i + 1) - 2 * b), cv::FONT_HERSHEY_SIMPLEX, 2, cvScalar(70, 55, 192, 0), 1, CV_AA);
                }
            }
        }
    }
}
