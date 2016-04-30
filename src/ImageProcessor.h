#pragma GCC diagnostic ignored "-Wpragmas"

#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <tesseract/baseapi.h>

//using namespace cv;
//using namespace std;

class ImageProcessor {
	private:
		std::vector<std::vector<cv::Point>> _squares;
		std::vector<std::vector<char>>& _board;
		cv::Mat& _sudokuImage;

		std::vector<int> _x;
		std::vector<int> _y;

	public:
		ImageProcessor(std::vector<std::vector<char>>&, cv::Mat&);
		void PopulateBoard();
		void RecordAnswers();

	private:
		double FindCosine(const cv::Point&, const cv::Point&, const cv::Point&);
		
};
