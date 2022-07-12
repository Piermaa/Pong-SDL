//#include "Ball.h"
//
///// <summary>
///// Inicializa las variables de la pelota, textuas, posicion, dimensiones
///// </summary>
///// <param name="renderer">El canva en el que se va a presentar la pelota</param>
///// <param name="ball"> Instancia del typedef struc de la pelota al cual se le modifican sus propiedades </param>
//void Ball_Initialize(Ball& ball, SDL_Renderer* renderer)
//{
//	ball.speedXBase = 50;
//	ball.speedYBase = 0;
//	ball.speedX = ball.speedXBase;
//	ball.surface = IMG_Load("Ball.png");
//	ball.texture = SDL_CreateTextureFromSurface(renderer, ball.surface);
//	SDL_FreeSurface(ball.surface);
//
//	ball.width = 40;
//	ball.height = 40;
//	ball.middle = 20;
//
//	ball.dest.h = ball.width;
//	ball.dest.w = ball.width;
//
//	ball.posX = 640;
//	ball.posY = 360;
//
//
//	ball.goesDown = true;
//	ball.goesLeft = true;
//}
//
///// <summary>
///// Copia la textura de la pelota en el renderer
///// </summary>
//void Ball_Render(Ball& ball, SDL_Renderer* renderer)
//{
//	SDL_RenderCopy(renderer, ball.texture, NULL, &ball.dest);
//}
//
///// <summary>
///// Se establecen las velocidades de la pelota en los difs ejes, esto sale de un deltaTime calculado en el main.cpp
///// </summary>
//void Ball_Speed(Ball& ball, float ballSpeedY, float ballSpeedX, float currentSpeed)
//{
//	ball.speedX = ballSpeedX * 3 + ball.xModif;
//	ball.speedY = ballSpeedY + ball.yModif;
//	speed = currentSpeed;
//}
//
///// <summary>
///// Calcula la velocidad de la pelota en el eje Y en base a en que parte de la paleta rebota. Tambien aumenta la velocidad en X de la pelota con cada rebote
///// </summary>
///// <param name="ballYr">posicion de la pelota en Y, pero es la esquina superior izquierda porque SDL REkT</param>
///// <param name="paleteY">posicion de la paleta en Y</param>
//void BallAngle(float ballYr, float paleteY)
//{
//	float ballY = ballYr + 25; //corrects the collider so the referenced value is on the middle of the ball
//	float pMiddle = paleteY + 100;
//	float pHeight = 200;
//
//	ball.yModif = 0;
//
//	if (abs(ballY - paleteY) < 80 || abs(ballY - paleteY) > 120)
//	{
//		ball.yModif = 7;
//	}
//	else
//	{
//		ball.yModif = 0;
//	}
//
//	if (abs(ballY - paleteY) > 80 && abs(ballY - paleteY) < pMiddle || abs(ballY - paleteY) < 120 && abs(ballY - paleteY) > pMiddle)
//	{
//		ball.yModif = 3;
//	}
//
//
//	//Se define si va para arriba o para abajo la pelota al rebotar contra la paleta
//	if (abs(ballY - paleteY) < 125)
//	{
//		ball.goesDown = false;
//	}
//	else
//	{
//		ball.goesDown = true;
//	}
//
//	//La velocidad en Y se basa en la velocidad en deltatime a la cual se le aplica una modificacion
//	ball.speedY = speed / 5 + ball.yModif;
//
//	ball.xModif += 0.4;
//
//	ball.speedX = speed * 2 + ball.xModif;
//}
//
///// <summary>
///// Actualiza la posicion de la pelota, se detecta la colision con las paletas y la hace rebotar contra los bordes superiores
///// </summary>
//void Ball_Update(Ball& ball, SDL_Rect destO, SDL_Rect destP)
//{
//
//	ball.dest.y = ball.posY - ball.middle;	//Actualiza la posicion de la pelota
//	ball.dest.x = ball.posX - ball.middle;
//
//	// Se decide si mover la pelota hacia la izquierda o la derecha
//	if (ball.goesLeft)
//	{
//		ball.posX -= ball.speedX;
//	}
//	else
//	{
//		ball.posX += ball.speedX;
//	}
//
//	//Se decide si mover la pelota hacia arriba o abajo
//	if (ball.goesDown)
//	{
//		ball.posY += ball.speedY;
//	}
//	else
//	{
//		ball.posY -= ball.speedY;
//	}
//
//	//Se detecta la colision contra los bordes superior e inferior de la pantalla
//	if (ball.posY < ball.middle)
//	{
//		ball.posY = ball.middle;
//		ball.goesDown = true;
//	}
//	if (ball.posY > 720 - ball.middle)
//	{
//		ball.posY = 720 - ball.middle;
//		ball.goesDown = false;
//	}
//
//	//Se detecta la colision con las paletas y se llama el metodo que va a calcular para donde y que tan fuerte va a rebotar
//	if ((ball.posX < destP.x + 100) && ((ball.posY >= destP.y - 20 && ball.posY <= destP.y + 200)))
//	{
//		ball.goesLeft = false;
//		BallAngle(ball.posY, destP.y);
//	}
//
//	if ((ball.posX > destO.x) && ((ball.posY >= destO.y - 20 && ball.posY <= destO.y + 200)))
//	{
//		ball.goesLeft = true;
//		BallAngle(ball.posY, destO.y);
//	}
//}