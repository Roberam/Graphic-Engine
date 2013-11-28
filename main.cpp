#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 midScreenX = screenX / 2;
const uint16 midScreenY = screenY / 2;
const int32 newAngle = 15;
const double speedAngle = 30;
const double speedMove = 120;

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(screenX, screenY, false);
	screen.Refresh();

	glfwSetMousePos(midScreenX, midScreenY);
	int32 xMouse = midScreenX;
	int32 yMouse = midScreenY;

	Sprite mySprite(ResourceManager::Instance().LoadImage("data/alien.png"));
	mySprite.SetBlendMode(Renderer::BlendMode::ALPHA);
	mySprite.SetPosition(midScreenX, midScreenY);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{
		xMouse = screen.GetMouseX();
		yMouse = screen.GetMouseY();

		if (mySprite.GetX() != xMouse || mySprite.GetY() != yMouse)
		{
			if (mySprite.GetX() < xMouse)
				mySprite.RotateTo(-newAngle, speedAngle);
			else if (xMouse < mySprite.GetX())
				mySprite.RotateTo(newAngle, speedAngle);
			mySprite.MoveTo((double)xMouse, (double)yMouse, speedMove);
		}
		else
			mySprite.RotateTo(0, speedAngle);

		mySprite.Update(screen.ElapsedTime());

		Renderer::Instance().Clear(0, 0, 255);
		mySprite.Render();

		// Refrescamos la pantalla
		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}
