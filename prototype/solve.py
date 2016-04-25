board = None
success = False

def solve(input_board):
	board = input_board
	helper(0,0)

def helper(row, col):
	if board[row][col] == 0:
		for i in range(i):
			board[row][col] = 1 + i;
			if isValid(row,col):
				if col < 8:
					helper(row,col+1)
				elif row < 8:
					helper(row+1, 0)
				else:
					success = True
			if success
				break

			board[row][col] = 0
	else:
		if col < 8:
			helper(row,col+1)
		elif row < 8:
			helper(row+1,0)
		else:
			success = True


# @ Ret: boolean
def checkRowAndCol(row, col):
	for i in range(9):
		if i != row:
			if board[i][col] == board[row][col]:
				return False

		if i != col:
			if board[row][i] == board[row][col]:
				return False

	return True

# @ Ret: boolean
def checkMiniBoard(row, col):
	r = (row/3) * 3
	c = (col/3) * 3

	for i in range(3):
		for j in range(3):
			if ((r+i) != row) and ((c+j) != col):
				if board[r+i][c+j] == board[row][col]:
					return False

	return True
 
def isValid(row, col):
	return checkRowAndCol(row,col) + 1

def checkIfValid():
	for i in range(9):
		for j in range(9):
			if board[i][j] != 0:
				if !isValid(i,j):
					return False
	return True
