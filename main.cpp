/*
 * =====================================================================================
 *
 *       Filename:  main.cpp (not done).
 *
 *    Description:  Simple implementation of Connect 4 in C++ with TUI.
 *    					Will be later implemented with GUI.
 *
 *        Version:  1.0
 *        Created:  12/02/2016 08:11:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author: youngthvg, 
 *   Organization: N/A
 *
 * =====================================================================================
 */
#include <iostream>
#include <vector>
using namespace std;

const int BOARDSZ = 6; // size of board
const char blank = ' '; // will be used for empty spaces in board. 
static bool over = false; // used to check if game is still live.
static bool turn = false; // false - 1st players turn, true - 2nd player's turn.
void initMatrix(vector< vector<char> > &grid){
	// just initializes the grid with o's.
	for(int y = 0; y < BOARDSZ; ++y){
		vector<char> row; // initialize row.
		for(int x = 0; x < BOARDSZ; ++x){
			row.push_back(' ');
		}
		grid.push_back(row);
	}
}
void printMatrix(vector< vector<char> > &grid){
	// simple procedure that will print items inside grid
	// not to be used to print the board !!
	for(int y = 0; y < grid.size(); ++y){
		for(int x = 0; x < grid[y].size(); ++x){
			cout << grid[y][x];
		}
		cout << "\n";
	}
}
bool isSpaceEmpty(char token){
	// will check if column and row has an empty space.
	return (token == blank);
}
int getNextRow(vector< vector<char> > &grid, int x){
	// will return the next avaliable row in a column.
	if(!isSpaceEmpty(grid[0][x])) return -1; // initial check to see if column is full.
	for(int y = grid.size() - 1; y > 0; --y){
		if(isSpaceEmpty(grid[y][x])) return y; //  if row is blank, return row.
	}
	return -1; // if column is already full.
}
bool isColEmpty(int y){
	// will check if column is full.
	return (y == - 1);
}
bool whoseTurn(){
	// false - 1st player, true - 2nd player.
	return turn;
}
void switchTurn(){
	// change the turn of the player.
	turn = !turn;
}
bool isEmpty(vector< vector<char> > &grid, int x, int y){
	return isSpaceEmpty(grid[y][x]);
}
char getPlayerToken(bool t){
	if(t) return 'X'; // 2nd player's turn.
	return 'O'; // 1st player's turn.
}
void setColumn(vector< vector<char> > &grid, int x, char token){
	// will emulate move.
	// error checking will be done somewhere else.
	int nxtRow = getNextRow(grid, x);
	if(!isColEmpty(nxtRow)) grid[nxtRow][x] = token; // set the string.
}
bool isPlayerPiece(char piece, bool t){
	return (getPlayerToken(t) == piece);
}
bool hasDiagonalWon(vector< vector<char> > &grid, int x, int y){
	// this function will be part of checking if a game has been won,
	// more specifically, it will check if the game has been won diagonallly.
	int ctr = 1; // will be used to keep track of consecutive peice.
	// check upper-right diagonal.
	for(int i = 1; ctr!= 4 && (y - i > -1 && x + i < BOARDSZ) && !isEmpty(grid, x + i, y - i) && isPlayerPiece(grid[y - i][x + i], whoseTurn()); ++i){
		++ctr;
	}
	// check lower-left diagonal.
	for(int i = 1; ctr != 4 && (y + i < BOARDSZ && x - i > -1) && !isEmpty(grid, x - i, y + i) && isPlayerPiece(grid[y + i][x - i], whoseTurn()); ++i){
		++ctr;
	}
	if(ctr == 4) return true; // diagonal was formed, so stop.
	
	// reset the counter, since we'll look at the other diagonal.
	ctr = 1;
	// upper-left diagonal.
	for(int i = 1; ctr != 4 && (y - i > -1 && x - i > -1) && !isSpaceEmpty(grid[y - i][x - i]) && isPlayerPiece(grid[y - i][x - i], whoseTurn()); ++i){
		++ctr;
	}
	// lower-right diagonal.
	for(int i = 1; ctr != 4 && (y + i < BOARDSZ && x + i < BOARDSZ) && !isSpaceEmpty(grid[y + i][x + i]) && isPlayerPiece(grid[y + i][x + i], whoseTurn()); ++i){
		++ctr;
	}
	return (ctr == 4); // see if diagonal was now formed.
}
bool hasLnWon(vector< vector<char> > &grid, int x, int y){
	// checks if player has won by horizontal line or vertical line.
	int ctr = 1;
	// check for right-horizontal line.
	for(int i = 1; ctr != 4 && (x + i < BOARDSZ) && !isSpaceEmpty(grid[y][x + i]) && isPlayerPiece(grid[y][x + i], whoseTurn()); ++i){
		++ctr;
	}
	// check for left-horizontal line.
	for(int i = 1; ctr != 4 && (x - i > -1) && !isSpaceEmpty(grid[y][x - i]) && isPlayerPiece(grid[y][x - i], whoseTurn()); ++i){
		++ctr;
	}
	if(ctr == 4) return true; // check if horizontal line was formed.
	// if no horizontal line, we'll check for vertical line.
	ctr = 1; // reset counter.
	// upper vertical line.
	for(int i = 1; ctr != 4 && (y - i > -1) && !isSpaceEmpty(grid[y - i][x]) && isPlayerPiece(grid[y - i][x], whoseTurn()); ++i)
	{
		++ctr;
	}
	// lower vertical line
	for(int i = 1; ctr != 4 && (y + i < BOARDSZ) && !isSpaceEmpty(grid[y + i][x]) && isPlayerPiece(grid[y + i][x], whoseTurn()); ++i)
	{
		++ctr;
	}
	return (ctr == 4); // check if vertical line was found.

}
void run(vector< vector<char> > &grid){
	int col;
	while(!over){
		if(whoseTurn()) cout << "2nd player go!\n";
		else cout << "1st player go!\n";
		do{
			cout << "Where would you like to drop a piece? (column)\n";
			cin >> col;
		}while(col < 0 || col > (BOARDSZ - 1));
		cout << "\n\n\n\n\n\n\n\n"; // clear screen
		int r = getNextRow(grid,col);
		setColumn(grid,col, getPlayerToken(whoseTurn()));
		printMatrix(grid);
		if(hasDiagonalWon(grid,col,r) || hasLnWon(grid, col, r)) over = true;
		else switchTurn();
	}
	cout << "------------GAME-OVER---------\nWINNER: PLAYER " << whoseTurn() << "\n";
}

int main(){
	vector< vector<char> > grid;
	initMatrix(grid);
	run(grid); // run game.
}
