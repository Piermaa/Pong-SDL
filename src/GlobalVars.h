#pragma once
#include <iostream>
#include <SDL.h>
#include <math.h>
#include <cstdlib>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Utils.h"
#include <string>

//Variables globales
SDL_Renderer* renderer;

SDL_Texture* paletaTexture;
SDL_Texture* oponentPaletaTexture;
SDL_Texture* centerLineTexture;

SDL_Texture* tutorialTexture;
SDL_Texture* startTexture;
SDL_Texture* timerTexture;
SDL_Texture* resultTexture;
SDL_Texture* playerPointsTexture;
SDL_Texture* oponentPointsTexture;


SDL_Texture* pongTexture;

SDL_Rect destPlayer;
SDL_Rect destOponent;
SDL_Rect destPText;
SDL_Rect destOText;
SDL_Rect destTimerText;
SDL_Rect destCenterLine;
SDL_Rect destStartText;
SDL_Rect destTutorialText;

SDL_Rect destResultText;
SDL_Rect destPong;

SDL_Surface* pongTextSurface;
SDL_Surface* playerPointsTextSurface;
SDL_Surface* oponentPointsTextSurface;
SDL_Surface* startTextSurface;
SDL_Surface* tutorialTextSurface;
SDL_Surface* timerTextSurface;
SDL_Surface* resultTextSurface;

TTF_Font* myFont;
TTF_Font* bigFont;
TTF_Font* mediumFont;

SDL_Color color = { 255,255,0 };

short unsigned int pointsR = 0;
short unsigned int pointsL = 0;
short unsigned int fontSize = 20;
short unsigned int bigFontSize=60;
short unsigned int middleFontSize = 40;
short int width = 90;
short int height = 200;
int middle = 100;
int const SPEED = 300;
short unsigned int leftLimit = 80;
short unsigned int rightLimit = 1190;
int ballStartPosY = 360;
int ballStartPosX = 640;
int limitUp = -10;
int limitDown = 520;
bool reachedDown;
bool reachedUp = true;
bool isGameRunning = false;
bool oponentGoesDown;
bool init = false;
bool paleteGoesDown = true;
bool opaleteGoesDown = true;


const float FPS = 60.0; //el doble q blodborne!!!!!!!
float startGameTime = 30;
float gameTime = startGameTime;
float deltaTimeInSeconds;
float currentSpeed;
float yModifier;
float xModifier;
float ballSpeedY = currentSpeed + yModifier;
float ballSpeedX = currentSpeed * 2 + xModifier;
float timeCorrection;
float delayTime = 1000.0f;
float oponentSpeedReduction = 1.5f;
float ballSpeedYReduction = 5;
float ballSpeedXReduction = 2;