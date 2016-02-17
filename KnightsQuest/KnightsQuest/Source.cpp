#include <cstdio>
#include <iostream>
#include <string>
#define MAXSIZE 10
using namespace std;


string startString = "\n\nTo create the grid, enter a number under 10 to determine the size or enter: ";
string& startS = startString;
string errorString = "\nThe number has to be between 5 and 9 to create a valid grid, please try again: ";
string& errorS = errorString;
string errorString2 = "\nThe starting position has to be in the grid, please try again: ";
string& errorS2 = errorString2;
const char quitChar = 'Q';

int posX;
int posY;

typedef struct chess_moves {
	int x, y;
}chess_moves;

void knightTour(int size);
bool findTour(int tour[10][10], chess_moves move_KT[], chess_moves curr_move, int move_count, int size);

int create(string startString) {
	char sizeChar;
	cout << startString;
	cin >> sizeChar;
	if (sizeChar == quitChar)
	{
		exit(0);
	}
	int size = sizeChar - '0';
	if (size < MAXSIZE && size > 4) {
		char *sizeC = &sizeChar;
		cout << "The memory allocated to the size is located at " << &sizeC;
		cout << "\nThe size of your grid will be " << size << " x " << size;
		cout << "\nAt which X coordinate do you want to start: ";
		cin >> posX;
		if (posX == quitChar)
		{
			exit(0);
		}
		cout << "At which Y coordinate do you want to start: ";
		cin >> posY;
		if (posY == quitChar)
		{
			exit(0);
		}
		if (size % 2 == 0 || size % 2 == 1 && (posX + posY) % 2 == 0) {
			if (posX < size && posY < size) {
				cout << "Calculating, this may take a couple of minutes depending on board size and starting position";
				knightTour(size);
			}
			else {
				create(errorS2);
			}
		}
		else {
			knightTour(0);
		}
	}
	else {
		create(errorS);
	}
	return 0;
}

int main(int argc, char ** argv)
{
	cout << "Insert Q at any input point to quit the app";
	create(startS);
}

void printTour(int tour[MAXSIZE][MAXSIZE], int size) {
	cout << "\n";
	int i, j;
	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			if (tour[i][j] < 10)
			{
				cout << "|  "<< tour[i][j] << "   |";
			}
			else 
			{ 
				cout << "|  "<< tour[i][j] << "  |"; 
			}
		}
		cout << "\n\n";
	}
	cout << "\nAbove is your knights tour solution";
	create("\nPress Q to quit the application or insert a new number:");
}


void knightTour(int size) {
	int tour[MAXSIZE][MAXSIZE];
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < size; j++) {
			tour[i][j] = -1;
		}
	}
	chess_moves move_KT[8] = { { 2,1 },{ 1,2 },{ -1,2 },{ -2,1 },
	{ -2,-1 },{ -1,-2 },{ 1,-2 },{ 2,-1 } };

	chess_moves curr_move = { posX,posY };

	if (findTour(tour, move_KT, curr_move, 0, size) == false) {
		cout << "\nKnight tour does not exist \n";
		create(startS);
	}
	else {
		printTour(tour, size);
	}
}

bool isMovePossible(chess_moves next_move, int tour[MAXSIZE][MAXSIZE], int size) {
	int i = next_move.x;
	int j = next_move.y;
	if ((i >= 0 && i < size) && (j >= 0 && j < size) && (tour[i][j] == -1))
		return true;
	return false;
}


bool findTour(int tour[MAXSIZE][MAXSIZE], chess_moves move_KT[], chess_moves curr_move, int move_count, int size) {
	int i;
	chess_moves next_move;
	if (move_count == 0) {
		tour[curr_move.x][curr_move.y] = 0;
	}
	if (move_count == size*size - 1) {
		return true;
	}
	for (i = 0; i < size; i++) {
		next_move.x = curr_move.x + move_KT[i].x;
		next_move.y = curr_move.y + move_KT[i].y;

		if (isMovePossible(next_move, tour, size)) {
			tour[next_move.x][next_move.y] = move_count + 1;
			if (findTour(tour, move_KT, next_move, move_count + 1, size) == true) {
				return true;
			}
			else {
				tour[next_move.x][next_move.y] = -1;
			}
		}
	}
	return false;
}
