import unittest

import parse_sudoku
import solve
import stackoverflow_answer


class TestSolver(unittest.TestCase):

    def test_answer(self):
        problem, answer = parse_sudoku.create_fake_board(5)
        print 'Problem:'
        print problem
        solved = stackoverflow_answer.solveSudoku(problem)
        if solve:
            print 'Solution:'
            print problem
            print 'Answer:'
            print answer
        else:
            print 'CANNOT BE SOLVED!'
        self.assertTrue(False)

    def test_solve(self):
        """Quick test sanity test case."""
        '''
        problem, answer = parse_sudoku.create_fake_board(5)
        print 'Problem:'
        print problem
        solved = solve.solve(problem)
        print 'Solution:'
        print solved
        print 'Answer:'
        print answer
        self.assertTrue(False)
        for c in range(9):
            for r in range(9):
                self.assertEqual(answer[c][r], solved[c][r])
        '''
        pass

if __name__ == '__main__':
    unittest.main()
