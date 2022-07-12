#pragma once
#include <iostream>
#include <SDL.h>
#include <math.h>
#include <cstdlib>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utils.h"
#include "SpaceShip.h"
#include <string>
#include "InputSistem.h"
#include "Ball.h"
#include "GlobalVars.h"
// NO PUDE HACER ANDAR EL TEXTO DESDE ESTE .h, ERA BUENA LA INTENCION )))))):

//
//TTF_Font* myFont;
//SDL_Color color = { 255,255,0 };


typedef struct Player
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};
typedef struct Oponent
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};
typedef struct Timer
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};
typedef struct Start
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};
typedef struct Tutorial
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
};
typedef struct Result 
{
	SDL_Surface* surface;
	SDL_Texture* texture;
	SDL_Rect rect;
}; 

Player player;
Oponent oponent;
Timer timer;
Start start;
Tutorial tutorial;
Result result;


void Text_Initialize(SDL_Renderer* renderer, Player &player)
{
	//myFont = TTF_OpenFont("assets/myFont.ttf", 20);

	start.surface = TTF_RenderText_Blended(myFont, "PRESS SPACE TO START SOLO, PRESS 2 TO START MULTIPLAYER", color);
	tutorial.surface = TTF_RenderText_Blended(myFont, "MOVE WITH UP & DOWN, OR A & W", color);
	

	start.texture = SDL_CreateTextureFromSurface(renderer, start.surface);
	tutorial.texture = SDL_CreateTextureFromSurface(renderer, tutorial.surface);
	//player.texture = SDL_CreateTextureFromSurface(renderer, player.surface);
	//oponent.texture = SDL_CreateTextureFromSurface(renderer, oponent.surface);

	SDL_FreeSurface(start.surface);
	SDL_FreeSurface(tutorial.surface);
	SDL_FreeSurface(oponent.surface);
	SDL_FreeSurface(player.surface);
	SDL_FreeSurface(timer.surface);
	SDL_FreeSurface(result.surface);
		
	player.rect.h = 50;
	player.rect.w = 30;
	player.rect.y = 100;
	player.rect.x = 680;

	oponent.rect.h = 50;
	oponent.rect.w = 30;
	oponent.rect.y = 100;
	oponent.rect.x = 580;

	start.rect.h = 50;
	start.rect.w = 1000;
	start.rect.y = 100;
	start.rect.x = 150;

	tutorial.rect.h = 30;
	tutorial.rect.w = 700;
	tutorial.rect.y = 500;
	tutorial.rect.x = 300;

	timer.rect.h = 50;
	timer.rect.w = 80;
	timer.rect.y = 600;
	timer.rect.x = 600;

}

void TextUpdate()
{

}

//startTextSurface = TTF_RenderText_Blended(myFont, "PRESS SPACE TO START SOLO, PRESS 2 TO START MULTIPLAYER", color);
//tutorialTextSurface = TTF_RenderText_Blended(myFont, "MOVE WITH UP & DOWN, OR A & W", color);


//playerPointsTextSurface = TTF_RenderText_Blended(myFont, "0"+pointsL, color);
//oponentPointsTextSurface = TTF_RenderText_Blended(myFont, "20"+ pointsR, color);

//timerTexture = SDL_CreateTextureFromSurface(renderer, timerTextSurface);
//startTexture = SDL_CreateTextureFromSurface(renderer, startTextSurface);
//tutorialTexture = SDL_CreateTextureFromSurface(renderer, tutorialTextSurface);