#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "logic.h"

using namespace std;

Board::Board(){
		for(int i = 0;i < HEIGHT; i++){
			for(int j = 0;j < WIDTH; j++){
				board[i][j] = Unopened_Cell;
			}
		}
}

bool Board::isValid(int row, int col){
    return (row >= 0) && (row < HEIGHT) && (col >= 0) && (col < WIDTH);
}

bool Board::isMine(int row,int col){
	if(board[row][col] == Mine_Cell) return true;
	else return false;
}

int Board::countAdjacentMines(int row, int col, int mine[][2]){
	int cnt = 0;
	
	int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
	
	for(int i = 0;i < 8; i++){
		int newRow = row + dx[i];
		int newCol = col + dy[i];
		
		if(isValid(newRow, newCol) && isMine(newRow, newCol)) cnt++;
	}
	return cnt;
}

void Board::placeMines(int mines[][2], int MINES){
    bool mark[HEIGHT][WIDTH];

    for(int i = 0;i < HEIGHT;i++){
    	for(int j = 0;j < WIDTH;j++){
    		mark[i][j] = false;
		}
	}

    for (int i = 0; i < MINES;) {
        int random1 = rand() % HEIGHT;
        int random2 = rand() % WIDTH;
        int x = random1;
        int y = random2;

        if (mark[random1][random2] == false) {
            
            mines[i][0] = x;
            mines[i][1] = y;

            board[mines[i][0]][mines[i][1]] = '*';
            mark[random1][random2] = true;
            i++;
        }
    }
    return;
}

bool Board::checkAround(int x, int y, int row, int col){
	bool check = true;
	int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
    int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
    for(int i = 0;i < 8;i++){
    	if(x != row + dx[i] && y != col + dy[i]) check = true;
    	else{
    		check = false;
    		break;
		}
	}
	return check == true;
}

void Board::replaceMine(int row, int col){
	for(int i = 0;i < HEIGHT;i++){
		for(int j = 0;j < WIDTH;j++){
			if(board[i][j] != Mine_Cell && checkAround(i, j, row, col)){
				board[i][j] = Mine_Cell;
				board[row][col] = Unopened_Cell;
				return;
			}
		}
	}
	return;
}