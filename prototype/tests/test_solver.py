import unittest

import parse_sudoku
import solve


class TestSolver(unittest.TestCase):

    def test_solve(self):
        """Quick test sanity test case."""
        problem, answer = parse_sudoku.create_fake_board(5)
        solved = solve.solve(problem)
        for c in range(answer.shape[1]):
            for r in range(answer.shape[0]):
                self.assertEqual(answer[c][r], solved[c][r])


if __name__ == '__main__':
    unittest.main()
