"""
This module is concerned with converting a solution array into an image.

TODO: More descriptions to be written.
"""
import numpy as np
import cv2


def resize_into_box(image, box_row, box_col):
    """Resize the given image into specified dimensions.

    Parameters
    ----------
    image : numpy array
        An image object created by `cv2.imread`.
    box_row : int
        Size of the row.
    box_col : int
        Size of the column.

    Returns
    -------
    numpy array
        The image object that is resized with `cv2.resize` function.
    """
    row, col = image.shape
    resized_image = cv2.resize(image, None, fx=(box_col/float(col)), fy=(box_row/float(row)), interpolation = cv2.INTER_CUBIC)
    return resized_image


def draw(answer):
    """Load images of numbers and stitch them into the given answer.
    
    Parameters
    ----------
    answer : numpy array
        2D numpy array that represented a fully solved Sudoku.

    See Also
    --------
    This function will create a file called `answer.jpg`.
    The file is a JPEG image that shows our Sudoku solution.
    """
    # TODO: This draw function needs to be separated into mutiples.
    temp_image = np.zeros((540,540), np.uint8)
    # TODO: Should these be constants?
    board_row = 540
    board_col = 540
    box_row = board_row / 9
    box_col = board_col / 9
    
    numbers = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
    number_images = list()

    for number in numbers:
        image = cv2.imread('numbers/{}.png'.format(number), 0)
        image = resize_into_box(image, box_row, box_col)
        number_images.append(image)

    for i in range(9):
        for j in range(9):
            temp_image[i*box_row:(i+1)*box_row,j*box_col:(j+1)*box_col] = number_images[int(answer[i][j])]

    cv2.imwrite('answer.jpg', temp_image)


def main():
    # Saving answer array - temporary.
    # testingArray = np.array([[ 7.,  8.,  3.,  9.,  2.,  6.,  1.,  4.,  5.],
    #                       [ 6.,  9.,  2.,  5.,  1.,  4.,  8.,  7.,  3.],
    #                       [ 1.,  5.,  4.,  3.,  8.,  7.,  6.,  2.,  9.],
    #                       [ 2.,  4.,  9.,  6.,  7.,  1.,  5.,  3.,  8.],
    #                       [ 5.,  6.,  7.,  4.,  3.,  8.,  2.,  9.,  1.],
    #                       [ 3.,  1.,  8.,  2.,  5.,  9.,  4.,  6.,  7.],
    #                       [ 4.,  7.,  6.,  1.,  9.,  5.,  3.,  8.,  2.],
    #                       [ 9.,  2.,  1.,  8.,  6.,  3.,  7.,  5.,  4.],
    #                       [ 8.,  3.,  5.,  7.,  4.,  2.,  9.,  1.,  6.]])
    # draw(testingArray)
    pass


if __name__ == '__main__':
    main()
