#ifndef _LOGIC__H
#define _LOGIC__H

#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"

class Board{
	
public:
	
	char board[HEIGHT + 1][WIDTH + 1];
	
	Board();
	
	bool isValid(int row, int col);
	
	bool isMine(int row,int col);

	int countAdjacentMines(int row, int col, int mine[][2]);

	void placeMines(int mines[][2], int MINES);

    bool checkAround(int x, int y, int row, int col);

	void replaceMine(int row, int col);

};

#endif 