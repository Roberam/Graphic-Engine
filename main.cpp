#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const double minScale = 0.5;
const double maxScale = 5.0;

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(800, 600, false);

	//Sprite mySprite(ResourceManager::Instance().LoadImage("data/ball.png"));
	Sprite mySprite(ResourceManager::Instance().LoadImage("data/soccer_npot.png"));
	mySprite.SetBlendMode(Renderer::BlendMode::SOLID);
	mySprite.SetPosition(400, 300);

	double ang = 0;
	const double incAng = 30;
	double scale = 1;
	const double incScale = 2;
	int16 stateScale = 1;

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{
		ang = WrapValue(ang + incAng * Screen::Instance().ElapsedTime(), 360);
		if (minScale < scale && stateScale == -1)
			scale = scale - incScale * Screen::Instance().ElapsedTime();
		else if (scale < maxScale && stateScale == 1)
			scale = scale + incScale * Screen::Instance().ElapsedTime();
		else
			stateScale = -stateScale;

		mySprite.SetAngle(ang);
		mySprite.SetScale(scale, scale);

		Renderer::Instance().Clear(0, 0, 0);
		mySprite.Render();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}
