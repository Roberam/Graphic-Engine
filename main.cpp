#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include <time.h>

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 midScreenX = screenX / 2;
const uint16 midScreenY = screenY / 2;
const uint16 rangeMin = 128;
const uint16 rangeMax = 255;
const uint16 colorMin = 0;
const uint16 colorMax = 255;
const double iniPosX = 200;
const double iniPosY = 100;
const String text = "Hola mundo";

uint16 Random(const uint16 min, const uint16 max)
{
	return (uint16)(min + (max - min) * (float)rand() / RAND_MAX);
}

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(screenX, screenY, false);
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	
	Font* myImageFont = ResourceManager::Instance().LoadFont("data/monospaced.png");
	srand((uint32)time(NULL));
	int16 speedX = Random(rangeMin, rangeMax);
	int16 speedY = Random(rangeMin, rangeMax);
	double posX = iniPosX;
	double posY = iniPosY;
	uint32 r = Random(colorMin, colorMax);
	uint32 g = Random(colorMin, colorMax);
	uint32 b = Random(colorMin, colorMax);
	bool collides = false;
	screen.Refresh();

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) )
	{
		// Limpiamos la pantalla.
		Renderer::Instance().Clear(0, 0, 0);
		
		//Actualizamos movimiento.
		posX = posX + speedX * screen.ElapsedTime();
		posY = posY + speedY * screen.ElapsedTime();

		// Comprobamos colisiones.
		if (posX <= 0 || screenX <= posX + myImageFont->GetTextWidth(text))
		{
			collides = true;
			speedX = -speedX;
		}
		if (posY <= 0 || screenY <= posY + myImageFont->GetTextHeight(text))
		{
			collides = true;
			speedY = -speedY;
		}
		
		// Mostramos texto.
		if (collides)
		{
			r = Random(colorMin, colorMax);
			g = Random(colorMin, colorMax);
			b = Random(colorMin, colorMax);
			Renderer::Instance().SetColor(r, g, b, 255);
			collides = false;
		}
		Renderer::Instance().DrawText(myImageFont, text, posX, posY);

		// Actualizamos la pantalla.
		screen.Refresh();
	}

	return 0;
}
