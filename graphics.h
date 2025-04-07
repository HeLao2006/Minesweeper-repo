#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "defs.h"
#include "logic.h"
#include<bits/stdc++.h>

using namespace std;

struct Graphics {
    SDL_Renderer *renderer;
	SDL_Window *window;

    SDL_Texture *cellUnopened, *cell0, *cell1, *cell2, *cell3, *cell4, *cell5, *cell6, *cell7, *cell8, 
	*cellFlag, *cellMine, *background, *smile, *dead, *cool, *menu, *settingIcon, *setting, *Redmine, *wrongFlag;
	
    TTF_Font *font = nullptr;

    void init();
    
    void render(const Board& myGame);
        
    void renderText(const string& s, const int& x, const int& y, const float& size, SDL_Color color);

	void renderSettingIcon();

	void renderSetting();

	void renderSmile();

	void renderDead();

	void renderCool();

	void renderMenu();
	
	void setBackground();
	
	void renderUI(int x,int y);
	
	void logErrorAndExit(const char* msg, const char* error);
    
	void initSDL();

    void prepareScene();
	
    void presentScene();
    
    SDL_Texture *loadTexture(const char *filename);

    void renderTexture(SDL_Texture *texture, int x, int y,int width,int height);
    
	void clearScreen();

    void quit();
    
};

#endif 