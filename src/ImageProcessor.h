#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <vector>

using namespace cv;
using namespace std;

class ImageProcessor {
	private:
		vector<vector<Point>> _squares;
		vector<vector<char>>& _board;
		Mat& _sudokuImage;

	public:
		ImageProcessor(vector<vector<char>>&, Mat&);
		void PopulateBoard();

	private:
		
};
