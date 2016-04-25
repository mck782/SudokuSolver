import unittest

import parse_sudoku
import solve


class TestSolver(unittest.TestCase):

    def test_solve(self):
        """Quick test sanity test case."""
        problem, answer = parse_sudoku.create_fake_board(5)
        print 'Problem:'
        print problem
        solved = solve.solve(problem)
        print 'Solution:'
        print solved
        print 'Answer:'
        print answer
        self.assertTrue(False)
        '''
        for c in range(9):
            for r in range(9):
                self.assertEqual(answer[c][r], solved[c][r])
        '''

if __name__ == '__main__':
    unittest.main()
