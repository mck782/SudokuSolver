#include "SudokuSolver.h"
#include "ImageProcessor.h"

using namespace cv;
using namespace std;

const char* windowName = "SudokuSolver";
const char* sudokuFile = "../data/sudoku.jpg";

int main() {
	namedWindow(windowName, 1);
	Mat sudokuImage = imread(sudokuFile, 1);

	imshow(windowName, sudokuImage);

	waitKey();

    return 0;
}