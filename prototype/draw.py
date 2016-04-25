import numpy as np
import cv2

# @ param : answer 2d list
def draw(answer):
	
	tempImage = np.zeros((540,540), np.uint8)
	
	boardrow = 540
	boardcol = 540
	boxRow = boardrow/9
	boxCol = boardcol/9

	zero = cv2.imread('numbers/zero.png',0)
	row,col = zero.shape
	zero = cv2.resize(zero, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	one = cv2.imread('numbers/one.png',0)
	row,col = one.shape
	one = cv2.resize(one, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	two = cv2.imread('numbers/two.png',0)
	row,col = two.shape
	two = cv2.resize(two, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	three = cv2.imread('numbers/three.png',0)
	row,col = three.shape
	three = cv2.resize(three, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	four = cv2.imread('numbers/four.png',0)
	row,col = four.shape
	four = cv2.resize(four, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	five = cv2.imread('numbers/five.png',0)
	row,col = five.shape
	five = cv2.resize(five, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	six = cv2.imread('numbers/six.png',0)
	row,col = six.shape
	six = cv2.resize(six, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	seven = cv2.imread('numbers/seven.png',0)
	row,col = seven.shape
	seven = cv2.resize(seven, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	eight = cv2.imread('numbers/eight.png',0)
	row,col = eight.shape
	eight = cv2.resize(eight, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)
	
	nine = cv2.imread('numbers/nine.png',0)
	row,col = nine.shape
	nine = cv2.resize(nine, None, fx=(boxCol/float(col)), fy=(boxRow/float(row)), interpolation = cv2.INTER_CUBIC)

	numberImages = [zero,one,two,three,four,five,six,seven,eight,nine]

	for i in range(9):
		for j in range(9):
			tempImage[i*boxRow:(i+1)*boxRow,j*boxCol:(j+1)*boxCol] = numberImages[int(answer[i][j])]

	cv2.imwrite('answer.jpg', tempImage)


# testingArray = np.array([[ 7.,  8.,  3.,  9.,  2.,  6.,  1.,  4.,  5.],
# 						[ 6.,  9.,  2.,  5.,  1.,  4.,  8.,  7.,  3.],
# 						[ 1.,  5.,  4.,  3.,  8.,  7.,  6.,  2.,  9.],
# 						[ 2.,  4.,  9.,  6.,  7.,  1.,  5.,  3.,  8.],
# 						[ 5.,  6.,  7.,  4.,  3.,  8.,  2.,  9.,  1.],
# 						[ 3.,  1.,  8.,  2.,  5.,  9.,  4.,  6.,  7.],
# 						[ 4.,  7.,  6.,  1.,  9.,  5.,  3.,  8.,  2.],
# 						[ 9.,  2.,  1.,  8.,  6.,  3.,  7.,  5.,  4.],
# 						[ 8.,  3.,  5.,  7.,  4.,  2.,  9.,  1.,  6.]])
# draw(testingArray)
