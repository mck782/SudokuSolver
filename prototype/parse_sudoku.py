import os
import random

import cv2
import numpy as np

import simple_ocr


def read_sudoku(filename):
    return cv2.imread(filename)


def cut_by_cell(image):
    x, y, color = image.shape
    row_block_size = x / 9;
    col_block_size = y / 9;

    row_offset = row_block_size / 10;
    col_offset = col_block_size / 10;
    
    board = np.zeros((9, 9))
    for i in range(9):
        row_beg = row_block_size * i
        row_end = row_block_size * (i + 1)
        for j in range(9):
            col_beg = col_block_size * j
            col_end = col_block_size * (j + 1)
            image_name = 'box{}{}.jpg'.format(j, i)
            #sliced_image = image[col_beg:col_end, row_beg:row_end]
            sliced_image = image[col_beg + col_offset : col_end - col_offset,
                                row_beg + row_offset : row_end - row_offset]
            number = simple_ocr.read_number_from_image(sliced_image)
            print 'number read as : {}'.format(number)
            simple_ocr.show_image(sliced_image)
            board[j][i] = number
    return board


def create_fake_board(level):
    """Create and return make board for test purpose."""
    def repeat_range(start):
        """Repeat 1-9 forever!"""
        num = start
        while (True):
            if num == 10:
                num = 1
            yield num
            num += 1

    # Our size is 9x9.
    board = np.zeros((9, 9))
    for c in range(board.shape[1]):
        gen = repeat_range(c+1)
        for r in range(board.shape[0]):
            board[r][c] = next(gen) 
    answer = board.copy()

    # Remove randomly chosen positions.
    for _ in range(level):
        r = random.randint(0, 8)
        c = random.randint(0, 8)
        board[r][c] = 0
    problem = board.copy()

    return problem, answer


def main():
    '''
    # Read in sudoku file.
    image = read_sudoku('sudoku.jpg')
    # Cut by cell.
    board = cut_by_cell(image)
    print board
    '''
    problem, answer = create_fake_board(5)


if __name__ == '__main__':
    main()
