#include <iostream>
using namespace std;

const int SIZE = 4;
const int goalNumber = 2048;
unsigned int scoreCounter(unsigned int currentscore, unsigned int a)
{
	currentscore += a;
	return currentscore;
}
bool printMatrix(int matrix[SIZE][SIZE])
{
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
			cout << matrix[i][j] << " ";
		cout << endl;
	}
	cout << endl;
	return 1;
}
bool newNumber(int matrix[SIZE][SIZE])
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			if (matrix[row][col] == 0)
			{
				matrix[row][col] = 2;
				return 1;
			}
			else
				continue;
		}
	}
}
int sortRight(int matrix[SIZE][SIZE], int n, int m)
{
	for (int i = 1; i < SIZE; i++)
	{
		if (matrix[n][m] == 0)
		{
			for (int col2 = m; col2 > 0; col2--)
			{
				matrix[n][col2] = matrix[n][col2 - 1];
				matrix[n][col2 - 1] = 0;
			}
		}
		else
			return 0;
	}
}
unsigned int moveRight(int matrix[SIZE][SIZE], unsigned int score)
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = SIZE-1; col>0; col--)
		{
			sortRight(matrix, row, col);
		}
	}
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = SIZE - 1; col > 0; col--)
		{
			if (matrix[row][col] == matrix[row][col - 1])
			{
				matrix[row][col] = 2 * matrix[row][col];
				matrix[row][col - 1] = 0;
				sortRight(matrix, row, col-1);
				score=scoreCounter(score, matrix[row][col]);
			}
			else
				continue;
		}
	}
	newNumber(matrix);
	cout << endl;
	printMatrix(matrix);
	cout << score << endl;
	return score;
}
int sortLeft(int matrix[SIZE][SIZE], int n, int m)
{
	for (int i = 1; i < SIZE; i++)
	{
		if (matrix[n][m] == 0)
		{
			for (int col2 = m; col2 < SIZE - 1; col2++)
			{
				matrix[n][col2] = matrix[n][col2 + 1];
				matrix[n][col2 + 1] = 0;
			}
		}
		else
			return 0;
	}
}
unsigned int moveLeft(int matrix[SIZE][SIZE], unsigned int score)
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			sortLeft(matrix, row, col);
		}
	}
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			if (matrix[row][col] == matrix[row][col + 1])
			{
				matrix[row][col] = 2 * matrix[row][col];
				matrix[row][col + 1] = 0;
				sortLeft(matrix, row, col+1);
				score = scoreCounter(score, matrix[row][col]);
			}
		}
	}
	newNumber(matrix);
	cout << endl;
	printMatrix(matrix);
	cout << score << endl;
	return score;
}
int sortUp(int matrix[SIZE][SIZE], int n, int m)
{
	for (int i = 1; i < SIZE; i++)
	{
		if (matrix[n][m] == 0)
		{
			for (int row2 = n; row2 < SIZE - 1; row2++)
			{
				matrix[row2][m] = matrix[row2 + 1][m];
				matrix[row2 + 1][m] = 0;
			}
		}
		else
			return 0;
	}
}
unsigned int moveUp(int matrix[SIZE][SIZE], unsigned int score)
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			sortUp(matrix, row, col);
		}
	}
	for (int col = 0; col < SIZE; col++)
	{
		for (int row = 0;row < SIZE; row++)
		{
			if (matrix[row][col] == matrix[row + 1][col])
			{
				matrix[row][col] = 2 * matrix[row][col];
				matrix[row+1][col] = 0;
				sortUp(matrix, row+1, col);
				score = scoreCounter(score, matrix[row][col]);
			}
		}
	}
	newNumber(matrix);
	cout << endl;
	printMatrix(matrix);
	cout << score << endl;
	return score;
}
int sortDown(int matrix[SIZE][SIZE], int n, int m)
{
	for (int i = 1; i < SIZE; i++)
	{
		if (matrix[n][m] == 0)
		{
			for (int row2 = n; row2 > 0; row2--)
			{
				matrix[row2][m] = matrix[row2 - 1][m];
				matrix[row2 - 1][m] = 0;
			}
		}
		else
			return 0;
	}
}
unsigned int moveDown(int matrix[SIZE][SIZE], unsigned int score)
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			sortDown(matrix, row, col);
		}
	}
	for (int col = 0; col < SIZE; col++)
	{
		for (int row = SIZE-1; row >0; row--)
		{
			if (matrix[row][col] == matrix[row - 1][col])
			{
				matrix[row][col] = 2 * matrix[row][col];
				matrix[row-1][col] = 0;
				sortDown(matrix, row, col);
				score = scoreCounter(score, matrix[row][col]);
			}
		}
	}
	newNumber(matrix);
	cout << endl;
	printMatrix(matrix);
	cout << score << endl;
	return score;
}

bool gameOver(char input)
{
	if (input == 'E')
	{
		cout << "Game Over";
		return 0;
	}
	else
		return 1;
}
bool gameOver2(int matrix[SIZE][SIZE])
{
	for (int row = 0; row < SIZE; row++)
	{
		for (int col = 0; col < SIZE; col++)
		{
			if (matrix[row][col] == goalNumber)
			{
				cout << "Congratulations you win";
				return 0;
			}
		}
	}
	return 1;
}

int main()
{
	int matrix[SIZE][SIZE] = { 2,0,1024,1024,0,0,0,0,0,0,0,0,0,0,0,0 };
	unsigned int score = 0;
	printMatrix(matrix);
	cout << "move:";
	char input = ' ';
	bool p = gameOver(input);
	do
	{
		cout << "move:";
		cin >> input;
		switch (input)
		{
			case 'R': score=moveRight(matrix, score); break;
			case 'L': score=moveLeft(matrix, score); break;
			case 'U': score=moveUp(matrix, score); break;
			case 'D': score=moveDown(matrix, score); break;
			case 'E': p=gameOver(input); break;
			default:
				cout << "Invalid input try again" << endl;
		}
	} while ((p == 1)&&(gameOver2(matrix)==1));

}
