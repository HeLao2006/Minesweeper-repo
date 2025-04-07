#include <bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include "defs.h"
#include "logic.h"
#include "game.h"

using namespace std;

int main(int argc, char** argv) {

	Board myBoard, realBoard;
	Game* minesweeper = new Game();
	
	TTF_Init();
	
	srand(time(0));
	minesweeper->playMinesweeper(realBoard, myBoard);
	
	return 0;
}