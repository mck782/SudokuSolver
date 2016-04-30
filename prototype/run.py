import os

import numpy as np

import parse_sudoku
import simple_ocr
import solve
import draw
import stackoverflow_answer


def test_run():
    # Temporary!
    numpy_filename = 'numpy_answer.npy'
    problem, _ = parse_sudoku.create_fake_board(5)
    print problem
    if numpy_filename in os.listdir('./'):
        print 'Answer file found! loading...'
        solved = True
        problem = np.load(numpy_filename)
    else:
        print 'Answer file not found, sovling...'
        solved = stackoverflow_answer.solveSudoku(problem)
    np.save(numpy_filename, problem)
    print 'Saved answer as "numpy_answer.npy"'
    if solved:
        # Draw answer. 
        draw.draw(problem)
        print 'Solved!'
        print 'Answer:'
        print problem
    else:
        print 'Cannot solve the problem.'
    print 'Done.'


def main():
    # Read in sudoku image file.
    board = parse_sudoku.main('sudoku.png')
    print 'Board is created.'
    problem = np.zeros(board.shape)
    # Read numbers.
    for c in range(9):
        for r in range(9):
            # problem[r][c] = simple_ocr.read_number_from_image(board[r][c])
            image_name = 'box{}{}.jpg'.format(r, c)
            problem[r][c] = simple_ocr.read_with_tesseract(image_name)
            # problem[r][c] = simple_ocr.read_number_from_file(image_name)
    print 'Numbers are read.'
    print problem
    solved = stackoverflow_answer.solveSudoku(problem)
    if solved:
        # Draw answer. 
        draw.draw(problem)
        print 'Solved!'
        print 'Answer:'
        print problem
    else:
        print 'Cannot solve the problem.'
    print 'Done.'

if __name__ == '__main__':
    main()
