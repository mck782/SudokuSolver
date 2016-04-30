"""
Load sudoku image into numpy array.
"""
import os
import random
import sys

import cv2
import numpy as np

import simple_ocr


def read_sudoku(filename):
    """Load sudoku image into numpy array.
    
    Parameters
    ----------
    filename : str
        Filename for sudoku image.

    Returns
    -------
    numpy array
        Array representation of loaded image.
    """
    return cv2.imread(filename)


def slice_image_into_numbers(image):
    """Slice given image by cells.

    Parameters
    ----------
    image : numpy array
        2D array that contains pixels as elements.

    Returns
    -------
    numpy array of numpy arrays
        2D array that contains blocks at each position.
        Each block represents image of a number.
    """
    x, y, color = image.shape
    row_block_size = x / 9;
    col_block_size = y / 9;

    row_offset = row_block_size / 10;
    col_offset = col_block_size / 10;
    
    board = np.zeros((9, 9), dtype=np.object)
    for col in range(9):
        col_beg = col_block_size * col
        col_end = col_block_size * (col + 1)
        for row in range(9):
            row_beg = row_block_size * row
            row_end = row_block_size * (row + 1)
            # sliced_image = image[row_beg:row_end, col_beg:col_end]
            sliced_image = image[row_beg + row_offset : row_end - row_offset,
                                 col_beg + col_offset : col_end - col_offset]
            image_name = 'box{}{}.jpg'.format(row, col)
            cv2.imwrite(image_name, sliced_image)
            number = sliced_image
            board[row][col] = number
    return board


def create_fake_board(level):
    """Create a sudoku problem, hard-coded.
    
    Parameters
    ----------
    level : int
        
    Returns
    -------
    tuple of numpy arrays
        Tuple of problem array and answer array.
    """
    board = np.zeros((9, 9))
    board[0] = np.array([0, 0, 0, 0, 2, 0, 0 ,0 ,5])
    board[1] = np.array([0, 9, 0, 0, 0, 0, 8 ,7 ,0])
    board[2] = np.array([0, 0, 0, 0, 8, 0, 6 ,2 ,0])
    board[3] = np.array([2, 0, 9, 0, 0, 0, 0 ,0 ,0])
    board[4] = np.array([5, 0, 0, 4, 0, 8, 0 ,0 ,1])
    board[5] = np.array([0, 0, 0, 0, 0, 0, 4 ,0 ,7])
    board[6] = np.array([0, 7, 6, 0, 9, 0, 0 ,0 ,0])
    board[7] = np.array([0, 2, 1, 0, 0, 0, 0 ,5 ,0])
    board[8] = np.array([8, 0, 0, 0, 4, 0, 0 ,0 ,0])
    return board, np.array(np.array([]))


def main(filename=None):
    """Load sudoku problem.

    Parameters
    ----------
    filename : str or None
        Filename for image to load.

    Returns
    -------
    numpy array
        Sudoku problem in array.

    See Also
    --------
    If `filename` is not given, a hard-coded problem will be returned.
    """
    if not filename:
        problem, answer = create_fake_board(5)
    else:
        image = read_sudoku(filename)
        problem = slice_image_into_numbers(image)
        answer = None
    print problem
    return problem


if __name__ == '__main__':
    try:
        filename = sys.argv[1]
    except IndexError:
        filename = None
    main(filename)
