#include <vector>

using namespace std;

class SudokuSolver {
	private:
		vector<vector<char>>& _board;
		bool _success;

	public:
		SudokuSolver(vector<vector<char>>&);
		void Solve();

	private:
		void SudokuSolverHelper(int, int);
		bool CheckRowAndCol(int, int);
		bool CheckMiniBoard(int, int);
		bool IsValid(int, int);
		bool CheckIfValid();	
};
