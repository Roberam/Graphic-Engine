#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 midScreenX = screenX / 2;
const uint16 midScreenY = screenY / 2;
const int32 newAngle = 15;
const double rAngle = 345;
const double lAngle = 15;
const double speedAngle = 15;
const double speedMove = 30;

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(screenX, screenY, false);
	glfwSetMousePos(midScreenX, midScreenY);

	Sprite mySprite(ResourceManager::Instance().LoadImage("data/alien.png"));
	mySprite.SetBlendMode(Renderer::BlendMode::ALPHA);
	mySprite.SetPosition(midScreenX, midScreenY);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{
		if (mySprite.GetX() != screen.GetMouseX() || mySprite.GetY() != screen.GetMouseY())
		{
			if (mySprite.GetX() < screen.GetMouseX())
				mySprite.RotateTo(-newAngle, speedAngle);
			else if (screen.GetMouseX() < mySprite.GetX())
				mySprite.RotateTo(newAngle, speedAngle);
			else
				mySprite.RotateTo(0, speedAngle);
			//mySprite.MoveTo((double)screen.GetMouseX(), (double)screen.GetMouseY(), speedMove);
		}
		mySprite.Update(screen.ElapsedTime());

		Renderer::Instance().Clear(0, 0, 255);
		mySprite.Render();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}
