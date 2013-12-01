#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <time.h>

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 speedMin = 128;
const uint16 speedMax = 255;
const uint8 alpha = 255;
const uint16 colorMin = 0;
const uint16 colorMax = 255;
const double iniPosX = 200;
const double iniPosY = 100;
const String text = "Hola, mundo";

uint16 Random(const uint16 min, const uint16 max)
{
	return (uint16)(min + (max - min) * (float)rand() / RAND_MAX);
}

int main(int argc, char* argv[]) {
	srand((uint32)time(NULL));
	Screen& screen = Screen::Instance();
	screen.Open(screenX, screenY, false);
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	
	Font* myImageFont = ResourceManager::Instance().LoadFont("data/arial16.png");
	uint32 textWidth = myImageFont->GetTextWidth(text);
	uint32 textHeight = myImageFont->GetTextHeight(text);
	int16 speedX = Random(speedMin, speedMax);
	int16 speedY = Random(speedMin, speedMax);
	double posX = iniPosX;
	double posY = iniPosY;
	bool collides = false;

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) )
	{
		// Actualizamos la pantalla.
		screen.Refresh();

		// Limpiamos la pantalla.
		Renderer::Instance().Clear(0, 0, 0);
		
		//Actualizamos movimiento.
		posX = posX + speedX * screen.ElapsedTime();
		posY = posY + speedY * screen.ElapsedTime();

		// Comprobamos colisiones.
		if (posX <= 0 || screenX <= posX + textWidth)
		{
			collides = true;
			speedX = -speedX;
		}
		if (posY <= 0 || screenY <= posY + textHeight)
		{
			collides = true;
			speedY = -speedY;
		}
		
		// Mostramos texto.
		if (collides)
		{
			uint8 r = Random(colorMin, colorMax);
			uint8 g = Random(colorMin, colorMax);
			uint8 b = Random(colorMin, colorMax);
			Renderer::Instance().SetColor(r, g, b, alpha);
			collides = false;
		}
		Renderer::Instance().DrawText(myImageFont, text, posX, posY);
	}

	return 0;
}
