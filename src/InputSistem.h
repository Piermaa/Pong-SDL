#pragma once
#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>


typedef struct InputState
{
	bool up;
	bool down;
	bool space;
	bool scndPlayer;
	bool restart;

	bool up2;
	bool down2;
};

InputState inputState;


/// <summary>
/// Establece que tecla se esta tocando y que instruccion desencadenar
/// </summary>
/// <param name="keyCode">numero que referencia a la tecla presionada</param>
void OnKeyDown(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_UP:
		inputState.up = true;
		break;

	case SDLK_DOWN:
		inputState.down = true;
		break;

	case SDLK_SPACE:
		inputState.space = true;
		inputState.scndPlayer = false;
		break;

	case SDLK_2:
		inputState.scndPlayer = true;
		inputState.space = false;
		break;

	case SDLK_r:
		inputState.restart = true;
		break;

	case SDLK_w:
		inputState.up2 = true;
		break;

	case SDLK_s:
		inputState.down2 = true;
		break;

	default:
		break;
	}
}

/// <summary>
/// Establece que tecla se esta soltando y que instruccion desencadenar
/// </summary>
/// <param name="keyCode">numero que referencia a la tecla soltada</param>
void OnKeyUp(int keyCode)
{
	switch (keyCode)
	{
	case SDLK_UP:
		inputState.up = false;
		break;
	case SDLK_DOWN:
		inputState.down = false;
		break;

	case SDLK_w:
		inputState.up2 = false;
		break;

	case SDLK_s:
		inputState.down2 = false;
		break;

	default:
		break;
	}
}

/// <summary>
/// Se procesan todos los eventos de input, teclas y propias de la ventana
/// </summary>
void Input_UpdateProssesing()
{
	SDL_Event event;

	while (SDL_PollEvent(&event)) // Se detectan todas las inputs realizadas y se llaman eventos en base a eso
	{
		switch (event.type)
		{
		case SDL_QUIT:
			exit(0);
			break;

		case SDL_KEYDOWN:
			OnKeyDown(event.key.keysym.sym);
			break;

		case SDL_KEYUP:
			OnKeyUp(event.key.keysym.sym);
			break;
		}
	}
}