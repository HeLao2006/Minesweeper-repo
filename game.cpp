#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "game.h"

using namespace std;

bool Game::isValid(int row, int col){
    return (row >= 0) && (row < HEIGHT) && (col >= 0) && (col < WIDTH);
}

bool Game::gameLoop(Board& myBoard, Board& realBoard, int mines[][2], int row, int col, int* movesLeft){
	if(myBoard.board[row][col] != Unopened_Cell) return false;
	
	if(realBoard.board[row][col] == Mine_Cell){
		myBoard.board[row][col] = RedMine_Cell;
		for(int i = 0;i < HEIGHT;i++){
			for(int j = 0;j < WIDTH;j++){
				if(realBoard.board[i][j] == Mine_Cell && myBoard.board[i][j] != RedMine_Cell) 
					myBoard.board[i][j] = Mine_Cell;
				if(realBoard.board[i][j] != Mine_Cell && myBoard.board[i][j] == Flag_Cell) 
					myBoard.board[i][j] = WrongFlag_Cell;
			}
		}
		graphics.renderDead();
		graphics.render(myBoard);
		graphics.presentScene();
		return true;
	}
	else{
		int cnt = realBoard.countAdjacentMines(row, col, mines);
		(*movesLeft)--;
		myBoard.board[row][col] = cnt + '0';
		if(!cnt){
			int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
			int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
			for(int i = 0;i < 8;i++){
				int newRow = row + dx[i];
				int newCol = col + dy[i];
				
				if(isValid(newRow, newCol) && !realBoard.isMine(newRow, newCol))
					gameLoop(myBoard, realBoard, mines, newRow, newCol, movesLeft);
			}
		}
		return false;
	}
}

void Game::resetGame(Board& myBoard, Board& realBoard, bool& gameOver, bool& flag, int& startTimer, 
int& currentTime, Uint32& startTick, string& timer){
	gameOver = false;
	flag = false;
	startTimer = 0;
	currentTime = 0;
	startTick = 0;
	timer = "00" + to_string(currentTime);
	for(int i = 0;i < HEIGHT; i++){
		for(int j = 0;j < WIDTH; j++){
			myBoard.board[i][j] = Unopened_Cell;
			realBoard.board[i][j] = Unopened_Cell;
		}
	}
}

void Game::playMinesweeper(Board& realBoard, Board& myBoard){
	graphics.init();
	
	SDL_Color color = {255, 0, 0, 255};
	
	int MINES = 28;
	bool menu = true;
	bool gameOver = false;
	int movesLeft = HEIGHT * WIDTH - MINES;
	int mines[MAXMINES][2];
	
	realBoard.placeMines(mines, MINES);
	
	bool flag = false;
	int x = 10, y = 10, currentTime = 0, stopTime = 0;
	SDL_Event event;
	int minesLeft = MINES;
	string s = "0" + to_string(minesLeft);
	int startTimer = 0;
	Uint32 startTick = 0, currentTick = 0, stopTick = 0, startSetting = 0;
	string timer = "00" + to_string(currentTime);
	
	bool inMenu = true;
	bool inSetting = false;
	
	while(!gameOver) {
		graphics.clearScreen();
		SDL_PollEvent(&event);
		if(inMenu){
			graphics.renderMenu();
			if (event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
				if(event.button.x >= 65 && event.button.x <= 425 
				&& event.button.y >= 305 && event.button.y <= 375){
					inMenu = false;
				}
			}
			else if(event.type == SDL_QUIT){
				gameOver = true;
				break;
			}
			SDL_Delay(16);
		}
		else{
			graphics.setBackground();
			graphics.renderUI(50,Board_Y / 4);
			graphics.renderUI(SCREEN_WIDTH - 115, Board_Y / 4);
			graphics.renderText(s, 50, Board_Y / 4, 2, color);
			graphics.renderText(timer, SCREEN_WIDTH - 115, Board_Y / 4, 2, color);
			graphics.renderSettingIcon();
			graphics.renderSmile();
//			graphics.render(realBoard);
			graphics.render(myBoard);
			
			if(inSetting){
				graphics.renderSetting();
				if(event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
					if(event.button.x >= 150 && event.button.x <= 350 
					&& event.button.y >= 180 + 40 && event.button.y <= 180 + 40 * 2){
						resetGame(myBoard, realBoard, gameOver, flag, startTimer, currentTime, startTick, timer);
						MINES = 28;
						realBoard.placeMines(mines, MINES);
						minesLeft = MINES;
						s = "0" + to_string(minesLeft);
						movesLeft = HEIGHT * WIDTH - MINES;
						inSetting = false;
					}
					else if(event.button.x >= 150 && event.button.x <= 350 
					&& event.button.y > 180 + 40 * 2 && event.button.y <= 180 + 40 * 3){
						resetGame(myBoard, realBoard, gameOver, flag, startTimer, currentTime, startTick, timer);
						MINES = 40;
						realBoard.placeMines(mines, MINES);
						minesLeft = MINES;
						s = "0" + to_string(minesLeft);
						movesLeft = HEIGHT * WIDTH - MINES;
						inSetting = false;
					}
					else if(event.button.x >= 150 && event.button.x <= 350 
					&& event.button.y > 180 + 40 * 3 && event.button.y <= 180 + 40 * 4){
						resetGame(myBoard, realBoard, gameOver, flag, startTimer, currentTime, startTick, timer);
						MINES = 71;
						realBoard.placeMines(mines, MINES);
						minesLeft = MINES;
						s = "0" + to_string(minesLeft);
						movesLeft = HEIGHT * WIDTH - MINES;
						inSetting = false;
					}
					else if(event.button.x >= 150 && event.button.x <= 350 
					&& event.button.y > 180 + 40 * 4 && event.button.y <= 180 + 40 * 5){
						stopTick = SDL_GetTicks();
						stopTime = (stopTick - startSetting) / 1000;
						inSetting = false;
					}
				}
				else if(event.type == SDL_QUIT){
					gameOver = true;
					break;
				}
				SDL_Delay(16);
			}
			else{
				graphics.presentScene();
				if(event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
					if(event.button.x >= Board_X && event.button.x <= Board_X + WIDTH * Cell_Size 
					&& event.button.y >= Board_Y && event.button.y <= Board_Y + HEIGHT * Cell_Size){
						y = (event.button.x - Board_X) / Cell_Size;
		    			x = (event.button.y - Board_Y) / Cell_Size;
		    			if(flag == false){
							int dx[9] = {-1, -1, -1, 0, 0, 1, 1, 1, 0};
							int dy[9] = {-1, 0, 1, -1, 1, -1, 0, 1, 0};
							for(int i = 0;i < 9;i++){
								int newx = x + dx[i];
								int newy = y + dy[i];
								if(isValid(newx, newy) && realBoard.isMine(newx, newy)) realBoard.replaceMine(newx, newy);
							}
							flag = true;
						}
						if(myBoard.board[x][y] != Unopened_Cell && myBoard.board[x][y] != Cell_0 
						&& myBoard.board[x][y] != Flag_Cell){
							int cntFlag = 0;
							int dx[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
							int dy[8] = {-1, 0, 1, -1, 1, -1, 0, 1};
							for(int i = 0;i < 8;i++){
								int newx = x + dx[i];
								int newy = y + dy[i];
								if(myBoard.board[newx][newy] == Flag_Cell) cntFlag++;
							}
							if(cntFlag == (int)myBoard.board[x][y] - 48){
								for(int i = 0;i < 8;i++){
									int newx = x + dx[i];
									int newy = y + dy[i];
									gameOver = gameLoop(myBoard, realBoard, mines, newx, newy, &movesLeft);
									if(gameOver) break;
								}
							}
						}
						if(startTimer ==  0) startTimer = 1;
						if(!gameOver) gameOver = gameLoop(myBoard, realBoard, mines, x, y, &movesLeft);
					}		
	    		}
	    		if(event.button.button == SDL_BUTTON_RIGHT && event.button.state == SDL_PRESSED){
	    			if(event.button.x >= Board_X && event.button.x <= Board_X + WIDTH * Cell_Size 
					&& event.button.y >= Board_Y && event.button.y <= Board_Y + HEIGHT * Cell_Size){
	    				int ry = (event.button.x - Board_X) / Cell_Size;
		    			int rx = (event.button.y - Board_Y) / Cell_Size;
			    		if(myBoard.board[rx][ry] == Unopened_Cell) {
			    			if(minesLeft > 0){
				    			myBoard.board[rx][ry] = Flag_Cell;
				    			minesLeft--;
				    			if(minesLeft > 9) s = "0" + to_string(minesLeft);
				    			else s = "00" + to_string(minesLeft);
				    		}
						}
			    		else if(myBoard.board[rx][ry] == Flag_Cell){
			    			myBoard.board[rx][ry] = Unopened_Cell;
			    			minesLeft++;
			    			if(minesLeft > 9) s = "0" + to_string(minesLeft);
				    		else s = "00" + to_string(minesLeft);
						}
						if(startTimer ==  0) startTimer = 1;
					}
				}
				if(startTimer == 1){
					startTick = SDL_GetTicks();
					startTimer = 2;
				}
				if(startTick != 0) {
					currentTick = SDL_GetTicks();
					currentTime = (currentTick - startTick) / 1000 - stopTime;	
					if(currentTime <= 9) timer = "00" + to_string(currentTime);
					else if(currentTime > 9 && currentTime <= 99) timer = "0" + to_string(currentTime);
					else timer = to_string(currentTime);
				}
				if(!gameOver && movesLeft == 0){
					graphics.renderCool();
					graphics.render(myBoard);
					graphics.presentScene();
					gameOver = true;
				}
				if( event.type == SDL_QUIT ){
					gameOver = true;
					break;
				}
				while(gameOver){
					SDL_PollEvent(&event);
					if(event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
						if(event.button.x >= Board_X + 7 * Cell_Size - 5 && event.button.x <= Board_X + 7 * Cell_Size + width + 5 
						&& event.button.y >= Board_Y / 4 && event.button.y <= Board_Y / 4 + height + 10){
							resetGame(myBoard, realBoard, gameOver, flag, startTimer, currentTime, startTick, timer);
							realBoard.placeMines(mines, MINES);
							minesLeft = MINES;
							s = "0" + to_string(minesLeft);
							movesLeft = HEIGHT * WIDTH - MINES;
						}
					}
					else if(event.type == SDL_QUIT) break;
				}
				if(event.button.button == SDL_BUTTON_LEFT && event.button.state == SDL_PRESSED){
					if(event.button.x >= Board_X + 7 * Cell_Size - 5 && event.button.x <= Board_X + 7 * Cell_Size + width + 5 
					&& event.button.y >= Board_Y / 4 && event.button.y <= Board_Y / 4 + height + 10){
						resetGame(myBoard, realBoard, gameOver, flag, startTimer, currentTime, startTick, timer);
						realBoard.placeMines(mines, MINES);
						minesLeft = MINES;
						s = "0" + to_string(minesLeft);
						movesLeft = HEIGHT * WIDTH - MINES;
					}
					else if(event.button.x >= 130 && event.button.x <= 130 + width 
					&& event.button.y >= Board_Y / 4 + 5 && event.button.y <= Board_Y / 4 + 5 + height){
						startSetting = SDL_GetTicks();
						stopTime = 0;
						inSetting = true;
					}
				}
				
				SDL_Delay(16);
			}
		}
	}
	graphics.quit();
	return;
}