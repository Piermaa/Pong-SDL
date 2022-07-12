#include <iostream>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <string>
#include "InputSistem.h"
#include "Ball.h"
#include "GlobalVars.h"

//#include <Ball>
//#include "Text.h"

using namespace std;

/// <summary>
/// Se inicializa el motor gráfico y se crea la ventana
/// </summary>
void StartGame() 
{
	SDL_Init(SDL_INIT_EVERYTHING);

	SDL_Window* window = SDL_CreateWindow("Pong", 100, 100, 1280, 720, SDL_WINDOW_SHOWN); // crea una ventana

	renderer = SDL_CreateRenderer(window, -1, 0); //crea un "canva" en el que se ponen las imagenes

	SDL_SetRenderDrawColor(renderer, 159, 100, 255, 255); // establece el color del canva

	TTF_Init();
}

/// <summary>
/// Se actualizan las detecciones de input 
/// </summary>
void UpdateInput()
{
	Input_UpdateProssesing();
}

// Se dibujan las texturas en el canvas que apareceran en el principio
void DrawTextures()
{
	Ball_Initialize(ball, renderer);
	
	
	myFont = TTF_OpenFont("assets/myFont.ttf", fontSize); //asigna la fuente y su tamaño
	bigFont = TTF_OpenFont("assets/myFont.ttf", bigFontSize);

	//Se cargan los assets en superficies y luego se asignan estas superficies al renderer

	SDL_Surface* pSurface = IMG_Load("Paleta.png");

	pongTextSurface= TTF_RenderText_Blended(bigFont, "PONG", color);
	startTextSurface = TTF_RenderText_Blended(myFont, "PRESS SPACE TO START SOLO, PRESS 2 TO START MULTIPLAYER", color);
	tutorialTextSurface = TTF_RenderText_Blended(bigFont, "MOVE WITH UP & DOWN, OR S & W", color);

	timerTexture = SDL_CreateTextureFromSurface(renderer, timerTextSurface);
	startTexture = SDL_CreateTextureFromSurface(renderer, startTextSurface);
	tutorialTexture = SDL_CreateTextureFromSurface(renderer, tutorialTextSurface);

	playerPointsTexture = SDL_CreateTextureFromSurface(renderer, playerPointsTextSurface);
	oponentPointsTexture = SDL_CreateTextureFromSurface(renderer, oponentPointsTextSurface);
	pongTexture = SDL_CreateTextureFromSurface(renderer, pongTextSurface);

	oponentPaletaTexture = SDL_CreateTextureFromSurface(renderer, pSurface);
	paletaTexture = SDL_CreateTextureFromSurface(renderer, pSurface);
	centerLineTexture = SDL_CreateTextureFromSurface(renderer, pSurface);

	//Evita memory leaks
	SDL_FreeSurface(timerTextSurface);
	SDL_FreeSurface(startTextSurface);
	SDL_FreeSurface(tutorialTextSurface);
	SDL_FreeSurface(playerPointsTextSurface);
	SDL_FreeSurface(oponentPointsTextSurface);
	SDL_FreeSurface(pSurface);


	// Se definen las propiedades de los rectangulos en los que se pegan las texturas

	destPlayer.h = height;
	destPlayer.w = width;
	destPlayer.x = 50;
	destPlayer.y = 260;

	destOponent.h = height;
	destOponent.w = width;
	destOponent.x = 1150;

	destPText.h = 50;
	destPText.w = 30;
	destPText.x = 680;
	destPText.y = 100;

	destOText.h = 50;
	destOText.w = 30;
	destOText.x = 580;
	destOText.y = 100;

	destStartText.h = 50;
	destStartText.w = 1000;
	destStartText.x = 140;
	destStartText.y = 400;

	destTutorialText.h = 60;
	destTutorialText.w = 700;
	destTutorialText.x = 290;
	destTutorialText.y = 600;

	destTimerText.h = 50;
	destTimerText.w = 80;
	destTimerText.x = 540;
	destTimerText.y = 600;

	destPong.h = 230;
	destPong.w = 300;
	destPong.x = 495;
	destPong.y = 100;

	destCenterLine.h = 1200;
	destCenterLine.w = 10;
	destCenterLine.x = 635;
	destCenterLine.y = -200;

}

void SecondPlayer()
{
	if (inputState.down2)
	{
		destOponent.y = destOponent.y + currentSpeed;
	}
	if (inputState.up2)
	{
		destOponent.y -= currentSpeed;
	}

	if (destOponent.y < limitUp)
	{
		destOponent.y = limitUp;
	}
	if (destOponent.y >= limitDown) {

		destOponent.y = limitDown;
	}
}

/// <summary>
/// Inteligencia artificial del oponente, basicamente se va para arriba si la pelota está mas arriba y viceversa
/// </summary>
/// <param name="oponentSpeed">velocidad a la que se mueve el oponente</param>
void OponentIA(float oponentSpeed)
{
	 // Para que el centro de la pelota apunte al centro de la paleta
	if (destOponent.y+middle < ball.posY + ball.middle)
	{
		destOponent.y += oponentSpeed;
	}
	else
	{
		destOponent.y -= oponentSpeed;
	}

	if (destOponent.y < limitUp)
	{
		destOponent.y = limitUp;
	}
	if (destOponent.y >= limitDown) 
	{
		destOponent.y = limitDown;
	}
}

/// <summary>
/// Reinicia las posiciones de los objetos y suma 1 punto al que lo haya hecho
/// </summary>
/// <param name="winnerPoints"></param>
void Restart(short unsigned int &winnerPoints)
{
	ball.posY = ballStartPosY;
	ball.posX = ballStartPosX;
	destOponent.y = ballStartPosY;
	winnerPoints++;

	ball.speedX = ball.speedXBase;
	ball.speedY = ball.speedYBase;

	ball.yModif = 0;
	ball.xModif = 0;
	
	Ball_Speed(ball, ballSpeedY, ballSpeedX, currentSpeed);
}

/// <summary>
/// Se reinicia el juego totalmente
/// </summary>
void RestartGame()
{
	Restart(pointsL);
	pointsL = 0;
	pointsR = 0;
	gameTime = startGameTime;
}

/// <summary>
/// Se actualizan los objetos y textos, se calcula el tiempo entre frames y se le resta tiempo al timer
/// </summary>
void updateGame() 
{
	if(inputState.restart)
	{
		RestartGame();
		inputState.restart = false;
	}
	// Actualizacion tiempo
	gameTime -= deltaTimeInSeconds;

	currentSpeed = SPEED * deltaTimeInSeconds;

	float oponentSpeed = currentSpeed / oponentSpeedReduction;
	ballSpeedY = currentSpeed / ballSpeedYReduction  + yModifier;
	ballSpeedX = currentSpeed / ballSpeedXReduction + xModifier;

	//------------------------------- oponents palete -------------------------//
	if(inputState.scndPlayer)
	{
		SecondPlayer();
	}
	else
	{
		OponentIA(oponentSpeed);
	}
	//----------------------------------------PLAYER----------------------------------------

	if (inputState.down)
	{
		destPlayer.y = destPlayer.y + currentSpeed;
	}
	if (inputState.up)
	{
		destPlayer.y -= currentSpeed;
	}

	if (destPlayer.y < -10)
	{
		destPlayer.y = -10;
	}
	if (destPlayer.y >= 520) {

		destPlayer.y = 520;
	}

	// -----------------------------------ball-----------------------------------// 

	Ball_Speed(ball, ballSpeedY, ballSpeedX, currentSpeed);
	Ball_Update(ball, destOponent,destPlayer);

	if (gameTime > 0)
	{
		if (ball.posX > rightLimit)
		{

			Restart(pointsL);
		}
		if (ball.posX < leftLimit)
		{
			Restart(pointsR);

		}
	}
}

void UpdateUI()
{
	string pointsLStr = to_string(pointsL);
	string pointsRStr = to_string(pointsR);

	int timerInt = round(gameTime);
	string timerStr = "00:" + to_string(timerInt);

	timerTextSurface = TTF_RenderText_Blended(myFont, timerStr.c_str(), color);
	oponentPointsTextSurface = TTF_RenderText_Blended(bigFont, pointsLStr.c_str(), color);
	playerPointsTextSurface = TTF_RenderText_Blended(bigFont, pointsRStr.c_str(), color);

	timerTexture = SDL_CreateTextureFromSurface(renderer, timerTextSurface);
	playerPointsTexture = SDL_CreateTextureFromSurface(renderer, playerPointsTextSurface);
	oponentPointsTexture = SDL_CreateTextureFromSurface(renderer, oponentPointsTextSurface);
}

void UpdateMenu()
{
	if (inputState.space || inputState.scndPlayer)
	{
		init=true;
	}
}


void DrawResult(SDL_Rect& dest, float x, float y, float h, float w, string text)
{
	resultTextSurface = TTF_RenderText_Blended(myFont, text.c_str(), color);
	dest.h = h;
	dest.w = w;
	dest.y = y;
	dest.x = x;
}

/// <summary>
/// Se limpia en canva, se copian las imagenes en el renderer con su transform actualizado y se presenta el renderer
/// </summary>
void Render()
{
	
	SDL_RenderClear(renderer);

	if(!init)
	{
		SDL_RenderCopy(renderer, pongTexture, NULL, &destPong);
		SDL_RenderCopy(renderer, startTexture, NULL, &destStartText);
		SDL_RenderCopy(renderer, tutorialTexture, NULL, &destTutorialText); //--------------------------------------------------------
	}
	else
	{
		if (gameTime < 0)
		{
			SDL_RenderCopy(renderer, playerPointsTexture, NULL, &destPText);
			SDL_RenderCopy(renderer, oponentPointsTexture, NULL, &destOText);

			if (pointsL < pointsR)
			{
				DrawResult(destResultText, 540, 500, 30, 200, "PLAYER 2 WINS");
			
			}
			if (pointsL > pointsR)
			{
				DrawResult(destResultText, 540, 500, 30, 200, "PLAYER 1 WINS");
	
			}
			if (pointsL == pointsR)
			{
				DrawResult(destResultText,590, 500, 30, 80, "Draw");

			}

			resultTexture = SDL_CreateTextureFromSurface(renderer, resultTextSurface);
			SDL_RenderCopy(renderer, resultTexture, NULL, &destResultText);
		}
		else
		{
			SDL_RenderCopy(renderer, playerPointsTexture, NULL, &destPText);
			SDL_RenderCopy(renderer, oponentPointsTexture, NULL, &destOText);
			SDL_RenderCopy(renderer, timerTexture, NULL, &destTimerText);

			SDL_RenderCopy(renderer, paletaTexture, NULL, &destPlayer);
			SDL_RenderCopy(renderer, oponentPaletaTexture, NULL, &destOponent);
			SDL_RenderCopy(renderer, centerLineTexture, NULL, &destCenterLine);
			Ball_Render(ball, renderer);
		}
	}

	SDL_RenderPresent(renderer);
}

/// <summary>
/// Punto de inicio de la ejecucion
/// </summary>
/// <returns>0</returns>
int main(int argc, char* args[])
{
	StartGame();
	DrawTextures();

	float previousTime = 0;
	float currentTime = 0;

	isGameRunning = true;

	while (isGameRunning) 
	{	
		if (!init)
		{	
			timeCorrection = SDL_GetTicks();
			UpdateInput();
			UpdateMenu();
			Render();	
		}
		else
		{
			previousTime = currentTime;
			currentTime = SDL_GetTicks() - timeCorrection;
			deltaTimeInSeconds = (currentTime - previousTime) / delayTime;
			// Limpio pantalla
			SDL_RenderClear(renderer);
			UpdateUI();
			UpdateInput();
			updateGame();
			Render();

			SDL_Delay(delayTime / FPS);
		}
		// Actualizo Timer
		
	}

	return 0;
}
