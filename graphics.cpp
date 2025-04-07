#include<bits/stdc++.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "graphics.h"

using namespace std;

void Graphics::init(){
        initSDL();
        cellUnopened = loadTexture("IMG//Minesweeper_unopened_square.png");
        cell0 = loadTexture("IMG//Minesweeper_0.png");
        cell1 = loadTexture("IMG//Minesweeper_1.png");
        cell2 = loadTexture("IMG//Minesweeper_2.png");
        cell3 = loadTexture("IMG//Minesweeper_3.png");
        cell4 = loadTexture("IMG//Minesweeper_4.png");
        cell5 = loadTexture("IMG//Minesweeper_5.png");
        cell6 = loadTexture("IMG//Minesweeper_6.png");
        cell7 = loadTexture("IMG//Minesweeper_7.png");
        cell8 = loadTexture("IMG//Minesweeper_8.png");
        cellFlag = loadTexture("IMG//Minesweeper_flag.png");
        cellMine = loadTexture("IMG//Minesweeper_mine.png");
        background = loadTexture("IMG//background.png");
        smile = loadTexture("IMG//Smile_Icon.png");
        dead = loadTexture("IMG//Dead_Icon.png");
        cool = loadTexture("IMG//Cool_Icon.png");
        menu = loadTexture("IMG//Menu.png");
        settingIcon = loadTexture("IMG//settings_icon.png");
        setting = loadTexture("IMG//Setting.png");
        Redmine = loadTexture("IMG//Minesweeper_redmine.png");
        wrongFlag = loadTexture("IMG//Minesweeper_notMine.png");
        font = TTF_OpenFont("Font//Digital.ttf", 13);
}

void Graphics::render(const Board& myGame){
	for (int i = 0; i < HEIGHT; i++)
        for (int j = 0; j < WIDTH; j++) {
            int x = Board_X + j * Cell_Size;
            int y = Board_Y + i * Cell_Size;
            switch (myGame.board[i][j]) {
                case Unopened_Cell: renderTexture(cellUnopened, x, y, width, height); break;
                case Cell_0: renderTexture(cell0, x, y, width, height); break;
                case Cell_1: renderTexture(cell1, x, y, width, height); break;
                case Cell_2: renderTexture(cell2, x, y, width, height); break;
                case Cell_3: renderTexture(cell3, x, y, width, height); break;
                case Cell_4: renderTexture(cell4, x, y, width, height); break;
                case Cell_5: renderTexture(cell5, x, y, width, height); break;
                case Cell_6: renderTexture(cell6, x, y, width, height); break;
                case Cell_7: renderTexture(cell7, x, y, width, height); break;
                case Cell_8: renderTexture(cell8, x, y, width, height); break;
                case Flag_Cell: renderTexture(cellFlag, x, y, width, height); break;
                case Mine_Cell: renderTexture(cellMine, x, y, width, height); break;
                case RedMine_Cell: renderTexture(Redmine, x, y, width, height); break;
                case WrongFlag_Cell: renderTexture(wrongFlag, x, y, width, height); break;
            };
        };
}

void Graphics::renderText(const string& s, const int& x, const int& y, const float& size, SDL_Color color) {
	SDL_Surface* textSurface = TTF_RenderText_Solid(font,  s.c_str(), color);
	SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_Rect textRect;
	textRect.w = textSurface->w * size;
	textRect.h = textSurface->h * size;
	textRect.x = x;
	textRect.y = y;
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	
	SDL_DestroyTexture(textTexture);
	SDL_FreeSurface(textSurface);
}

void Graphics::renderSettingIcon(){
	renderTexture(settingIcon, 130, Board_Y / 4 + 5, width, height);
}

void Graphics::renderSetting(){
	renderTexture(setting, 150, 180, 200, 200);
	presentScene();
}

void Graphics::renderSmile(){
	renderTexture(smile, Board_X + 7 * Cell_Size - 5, Board_Y / 4, width + 10, height + 10);
}

void Graphics::renderDead(){
	renderTexture(dead, Board_X + 7 * Cell_Size - 5, Board_Y / 4, width + 10, height + 10);
}

void Graphics::renderCool(){
	renderTexture(cool, Board_X + 7 * Cell_Size - 5, Board_Y / 4, width + 10, height + 10);
}

void Graphics::logErrorAndExit(const char* msg, const char* error){
    
    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
    SDL_Quit();
}

void Graphics::initSDL(){
	const char* WINDOW_TITLE = "Minesweeper";
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        
//      window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
//		 SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP); //fullscreen
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
}
    
void Graphics::setBackground(){

    SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, background, NULL, NULL);
}

void Graphics::renderMenu(){
	SDL_RenderClear(renderer);
    SDL_RenderCopy( renderer, menu, NULL, NULL);
    presentScene();
}

void Graphics::renderUI(int x,int y){
	SDL_Rect fill_rect;
	fill_rect.x = x;
	fill_rect.y = y;
	fill_rect.w = 60;
	fill_rect.h = 40;
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 100);
	SDL_RenderFillRect(renderer, &fill_rect);
	SDL_Color color = {255, 0, 0, 75};
	renderText("888", x, y, 2, color);
}

void Graphics::prepareScene(){

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
}

void Graphics::presentScene(){

    SDL_RenderPresent(renderer);
}

SDL_Texture* Graphics::loadTexture(const char *filename){

    SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

    SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
    if (texture == NULL)
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

    return texture;
}

void Graphics::renderTexture(SDL_Texture *texture, int x, int y,int width,int height){

    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = width;
    dest.h = height;

    SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Graphics::clearScreen(){
	SDL_RenderClear(renderer);
}

void Graphics::quit(){
    SDL_DestroyTexture(cellUnopened);
    cellUnopened = nullptr;
    SDL_DestroyTexture(cell0);
    cell0 = nullptr;
    SDL_DestroyTexture(cell1);
    cell1 = nullptr;
    SDL_DestroyTexture(cell2);
    cell2 = nullptr;
    SDL_DestroyTexture(cell3);
    cell3 = nullptr;
    SDL_DestroyTexture(cell4);
    cell4 = nullptr;
    SDL_DestroyTexture(cell5);
    cell5 = nullptr;
    SDL_DestroyTexture(cell6);
    cell6 = nullptr;
    SDL_DestroyTexture(cell7);
    cell7 = nullptr;
    SDL_DestroyTexture(cell8);
    cell8 = nullptr;
    SDL_DestroyTexture(cellFlag);
    cellFlag = nullptr;
    SDL_DestroyTexture(cellMine);
    cellMine = nullptr;
    SDL_DestroyTexture(background);
    background = nullptr;
    SDL_DestroyTexture(smile);
    smile = nullptr;
    SDL_DestroyTexture(dead);
    dead = nullptr;
    SDL_DestroyTexture(cool);
    cool = nullptr;
    SDL_DestroyTexture(menu);
    menu = nullptr;
    SDL_DestroyTexture(Redmine);
    Redmine = nullptr;
    SDL_DestroyTexture(wrongFlag);
    wrongFlag = nullptr;
    
	TTF_CloseFont(font);

    IMG_Quit();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}