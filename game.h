#ifndef _GAME__H
#define _GAME__H

#pragma once
#include<bits/stdc++.h>
#include<SDL.h>
#include<SDL_image.h>
#include "defs.h"
#include "logic.h"
#include "graphics.h"

using namespace std;

class Game{

public:
	
	Graphics graphics;
	
	bool isValid(int row, int col);

	bool gameLoop(Board& myBoard, Board& realBoard, int mines[][2], int row, int col, int* movesLeft);

	void resetGame(Board& myBoard, Board& realBoard, bool& gameOver, bool& flag, int& startTimer, 
	int& currentTime, Uint32& startTick, string& timer);

	void playMinesweeper(Board& realBoard, Board& myBoard);

};

#endif