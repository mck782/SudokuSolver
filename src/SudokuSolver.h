// ------------------
// SudokuSolver.h
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

#include <vector>

/**
 * Class that solves the sudoku board.
 */
class SudokuSolver {
private:
	std::vector<std::vector<char>>& _board;
	bool _success;

public:
	/**
     * Constructor for SudokuSolver class.
     * @param std::vector<std::vector<char>>& reference to the sudoku board.
     */
	SudokuSolver(std::vector<std::vector<char>>&);

	/**
     * Solves the board.
     */
	void Solve();

private:
	void SudokuSolverHelper(int, int);
	bool CheckRowAndCol(int, int);
	bool CheckMiniBoard(int, int);
	bool IsValid(int, int);
	bool CheckIfValid();
};
