#include <iostream>
using namespace std;

const int SIZE = 10;

int isBoardSizeCorrectInput(int boardSIze)
{
	while ((boardSIze < 3) || (boardSIze > 99))
	{
		cout << "Board size must be between 3 and 10. Try again!";
		cin >> boardSIze;
	}
	return boardSIze;
}

void isNumberOfMinesCorrectInput(int boardSIze, int& numberOfMines)
{
	while ((numberOfMines < 1) || (numberOfMines > 3 * boardSIze))
	{
		cout << "Incorect input! The number of mines must be between 1 and 3* the size of the board. Try again!";
		cin >> numberOfMines;
	}
}

void printBoard(char board[SIZE][SIZE], int boardSize)
{
	system("CLS");
	for (int j = 0; j <= boardSize; j++)
	{
		for (int k = 0; k <= boardSize; k++)
			cout <<"| "<< board[j][k]<<" ";
		cout << endl;
	}
}

void createBoard(char board[SIZE][SIZE], int boardSize, char fillingSymbol)
{
	for (int i = 0; i <= boardSize; i++)
	{
		for (int j = 0; j <= boardSize; j++)
			board[i][j] = fillingSymbol;
	}
}

void isItEmptySquare(char behindBoard[SIZE][SIZE], int boardSize, int x, int y)
{
	if (behindBoard[x][y] == ' ')
		behindBoard[x][y] = '1';
	else
		behindBoard[x][y]++;
}

void numberOfBombs(char behindBoard[SIZE][SIZE], int boardSize, int x, int y)
{
	if (x < 1)
	{
		if (y < 1)
		{
			if (behindBoard[x][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y + 1));
			if (behindBoard[x + 1][y] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y));
			if (behindBoard[x + 1][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y + 1));
		}
		else if (y > boardSize - 1)
		{
			if (behindBoard[x][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y - 1));
			if (behindBoard[x + 1][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y - 1));
			if (behindBoard[x + 1][y] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y));
		}
		else
		{
			if (behindBoard[x][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y - 1));
			if (behindBoard[x][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y + 1));
			if (behindBoard[x + 1][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y - 1));
			if (behindBoard[x + 1][y] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y));
			if (behindBoard[x + 1][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x+1), (y + 1));
		}
	}
	else if (x > boardSize - 1)
	{
		if (y < 1)
		{
			if (behindBoard[x - 1][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x-1), (y + 1));
			if (behindBoard[x - 1][y] != '@')
				isItEmptySquare(behindBoard, boardSize, (x-1), (y));
			if (behindBoard[x][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y + 1));
		}
		else if (y > boardSize - 1)
		{
			if (behindBoard[x][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y - 1));
			if (behindBoard[x - 1][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x -1), (y - 1));
			if (behindBoard[x - 1][y] != '@')
				isItEmptySquare(behindBoard, boardSize, (x - 1), (y));
		}
		else
		{
			if (behindBoard[x][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y - 1));
			if (behindBoard[x][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x), (y + 1));
			if (behindBoard[x - 1][y - 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x - 1), (y - 1));
			if (behindBoard[x - 1][y] != '@')
				isItEmptySquare(behindBoard, boardSize, (x -1), (y));
			if (behindBoard[x - 1][y + 1] != '@')
				isItEmptySquare(behindBoard, boardSize, (x -1), (y + 1));
		}
	}
	else
	{
		if (behindBoard[x - 1][y - 1] != '@')
			isItEmptySquare(behindBoard, boardSize, (x-1), (y - 1));
		if (behindBoard[x - 1][y + 1] != '@')
			isItEmptySquare(behindBoard, boardSize, (x-1), (y + 1));
		if (behindBoard[x - 1][y] != '@')
			isItEmptySquare(behindBoard, boardSize, (x-1), (y));;
		if (behindBoard[x][y - 1] != '@')
			isItEmptySquare(behindBoard, boardSize, (x), (y - 1));
		if (behindBoard[x][y + 1] != '@')
			isItEmptySquare(behindBoard, boardSize, (x), (y + 1));
		if (behindBoard[x + 1][y - 1] != '@')
			isItEmptySquare(behindBoard, boardSize, (x+1), (y - 1));
		if (behindBoard[x + 1][y] != '@')
			isItEmptySquare(behindBoard, boardSize, (x+1), (y));
		if (behindBoard[x + 1][y + 1] != '@')
			isItEmptySquare(behindBoard, boardSize, (x+1), (y + 1));
	}
}

void bombInput(char behindBoard[SIZE][SIZE], int boardSize, int numberOfMines)
{
	for (int i=0; i< numberOfMines; i++)
	{
		int x = (rand() % boardSize);
		int y = (rand() % boardSize);
		if (behindBoard[x][y] == '@')
			i--;
		else
		{
			behindBoard[x][y] = '@';
			numberOfBombs(behindBoard, boardSize, x, y);
		}
	}
}

int markSquare(char upfrontBoard[SIZE][SIZE], char behindBoard[SIZE][SIZE], int x, int y, int& countOfMarkedSymbols)
{
	if (upfrontBoard[x][y] == '#')
	{
		upfrontBoard[x][y] = 'X';
		if(behindBoard[x][y]=='@')
			countOfMarkedSymbols++;
		return countOfMarkedSymbols;
	}
	else
		cout << "Invaild input or comand. Try again!";
}

void unmarkSquare(char upfrontBoard[SIZE][SIZE], int x, int y)
{
	if (upfrontBoard[x][y] == 'X')
		upfrontBoard[x][y] = '#';
	else
		cout << "Invaild input or comand. Try again!";
}

bool openSquare(char upfrontBoard[SIZE][SIZE], char behindBoard[SIZE][SIZE], int boardSize, int x, int y);

void openAnEmptySquare(char upfrontBoard[SIZE][SIZE], char behindBoard[SIZE][SIZE], int boardSize, int x, int y)
{
	openSquare(upfrontBoard, behindBoard, boardSize, (x - 1), (y - 1));
	openSquare(upfrontBoard, behindBoard, boardSize, (x - 1), y);
	openSquare(upfrontBoard, behindBoard, boardSize, (x - 1), (y + 1));
	openSquare(upfrontBoard, behindBoard, boardSize, x, (y - 1));
	openSquare(upfrontBoard, behindBoard, boardSize, x, (y + 1));
	openSquare(upfrontBoard, behindBoard, boardSize, (x + 1), (y - 1));
	openSquare(upfrontBoard, behindBoard, boardSize, (x + 1), y);
	openSquare(upfrontBoard, behindBoard, boardSize, (x + 1), (y + 1));
}

bool openSquare(char upfrontBoard[SIZE][SIZE], char behindBoard[SIZE][SIZE],int boardSize, int x, int y)
{
	if (upfrontBoard[x][y] == behindBoard[x][y])
	{
		return 1;
	}
	else
	{
		upfrontBoard[x][y] = behindBoard[x][y];
		if (upfrontBoard[x][y] == '@')
			return 0;
		else if (upfrontBoard[x][y] == ' ')
			openAnEmptySquare(upfrontBoard, behindBoard, boardSize, x, y);
		else
			return 1;
	}
	
}

bool isComandOpen(char comand[SIZE])
{
	return ((comand[0] == 'o') && (comand[1] == 'p') && (comand[2] == 'e') && (comand[3] == 'n') && (comand[4] == '\0'));
}

bool isComandMark(char comand[SIZE])
{
	return ((comand[0] == 'm') && (comand[1] == 'a') && (comand[2] == 'r') && (comand[3] == 'k') && (comand[4] == '\0'));
}

bool isComandUnmark(char comand[SIZE])
{
	return ((comand[0] == 'u') && (comand[1] == 'n') && (comand[2] == 'm') && (comand[3] == 'a') && (comand[4] == 'r')&& (comand[5] == 'k')&&(comand[6] == '\0'));
}

bool areAllMinesMarked(int numberOfMines, int countOfMarkedSymbols)
{
	return!(numberOfMines == countOfMarkedSymbols);
}

int main()
{
	int boardSize, numberOfMines, countOfMarkedSymbols=0;
	char fillingSymbolUpfront = '#', fillingSymbolBehind = ' ';
	cout << "Size=";
	cin >> boardSize;
	boardSize=isBoardSizeCorrectInput(boardSize);
	char upfrontBoard[SIZE][SIZE], behindBoard[SIZE][SIZE];
	createBoard(upfrontBoard, boardSize, fillingSymbolUpfront);
	printBoard(upfrontBoard, boardSize);
	createBoard(behindBoard, boardSize, fillingSymbolBehind);
	cout << "Number of mines=";
	cin >> numberOfMines;
	isNumberOfMinesCorrectInput(boardSize, numberOfMines);
	bombInput(behindBoard, boardSize, numberOfMines);
	printBoard(behindBoard, boardSize);
	bool openedAMine=true;
	do
	{
		printBoard(upfrontBoard, boardSize);
		char comand[SIZE];
		int x, y;
		cout << "Comand:";
		while ((getchar()) != '\n');
		cin.getline(comand, SIZE);
		cout << "Coordinates:";
		cin >> x >> y;
		if (isComandOpen(comand))
			openedAMine=openSquare(upfrontBoard, behindBoard, boardSize, x, y);
		else if (isComandMark(comand))
			markSquare(upfrontBoard,behindBoard, x, y, countOfMarkedSymbols);
		else if (isComandUnmark(comand))
			unmarkSquare(upfrontBoard, x, y);
		else
			cout << "Invalid comand. Please try again!" << endl;;
	} while (areAllMinesMarked(numberOfMines, countOfMarkedSymbols)&&(openedAMine));
	if (!openedAMine)
	{
		printBoard(behindBoard, boardSize);
		cout << "You lose!";
	}
	else
		cout << "Congratulations you win!";
	
}
