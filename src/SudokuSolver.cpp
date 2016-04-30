// ------------------
// SudokuSolver.c++
// Copyright (C) 2016
// Mikkel C. Kim
// Hyunchel Kim
// Jungmo Ku
// ------------------

#include "SudokuSolver.h"

SudokuSolver::SudokuSolver(std::vector<std::vector<char>>& board) : _board(board), _success(false)
{}

void SudokuSolver::Solve() {
	SudokuSolverHelper(0, 0);
}

void SudokuSolver::SudokuSolverHelper(int row, int col) {
	if(_board[row][col] == '.') {
		for(int i = 0; i < 9; ++i) {
			_board[row][col] = '1' + i;
			if(IsValid(row, col)) {
				if(col < 8) {
					SudokuSolverHelper(row, col + 1);
				} else if(row < 8) {
					SudokuSolverHelper(row + 1, 0);
				} else {
					_success = true;
				}
			} 

			if(_success)
				break;

			_board[row][col] = '.';
		}
	} else {
		if(col < 8) {
			SudokuSolverHelper(row, col + 1);
		} else if(row < 8) {
			SudokuSolverHelper(row + 1, 0);
		} else {
			_success = true;
		}
	}
}

bool SudokuSolver::CheckRowAndCol(int row, int col) {
	for(int i = 0; i < 9; ++i) {
		if(i != row) {
			if(_board[i][col] == _board[row][col]) {
				return false;
			}
		}
		if(i != col) {
			if(_board[row][i] == _board[row][col]) {
				return false;
			}
		}
	}
	return true;
}

bool SudokuSolver::CheckMiniBoard(int row, int col) {	
	int r = (row / 3) * 3;
	int c = (col / 3) * 3;

	for(int i = 0; i < 3; ++i) {
		for(int j = 0; j < 3 ; ++j) {
			if(r + i != row && c + j != col) {
				if(_board[r + i][c + j] == _board[row][col]) {
					return false;
				}
			}
		}
	}
	return true;
}

bool SudokuSolver::IsValid(int row, int col) {
	return CheckRowAndCol(row, col) && CheckMiniBoard(row, col);
}

bool SudokuSolver::CheckIfValid() {
	for(int i = 0; i < 9; ++i) {
		for(int j = 0; j < 9; ++j) {
			if(_board[i][j] != '.') {
				if(!IsValid(i, j)) {
					return false;
				}
			}
		}
	}
	return true;
}
