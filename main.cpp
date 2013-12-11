#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/InputManager.h"

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 midScreenX = screenX / 2;
const uint16 midScreenY = screenY / 2;

const String MOUSE_BUTTON_L = "MOUSE_BUTTON_LEFT";
const String MOUSE_BUTTON_R = "MOUSE_BUTTON_RIGHT";

/*
const double backMoveX = 32;
const double backMoveY = 32;
const double backRelX = 0.8;
const double backRelY = 0.8;
const double frontMoveX = -32;
const double frontMoveY = 32;
const double frontRelX = 1;
const double frontRelY = 1;

const int16 moveSpeed = 256;
const int32 spriteAngle = 15;
const double angleSpeed = 30;

const String UP = "ARRIBA";
const String DOWN = "ABAJO";
const String LEFT = "IZQUIERDA";
const String RIGHT = "DERECHA";
*/

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	const Renderer& render = Renderer::Instance();
	ResourceManager& rm = ResourceManager::Instance();

	screen.Open(screenX, screenY, false);
	render.SetBlendMode(Renderer::BlendMode::ALPHA);
	screen.Refresh();

	Image* myImage = rm.LoadImage("data/star.png");
	Scene myScene = Scene();
	Sprite* mySprite = myScene.CreateSprite(myImage);
	double mouseX = midScreenX;
	double mouseY = midScreenY;
	glfwSetMousePos(mouseX, mouseY);
	mySprite->SetPosition(mouseX, mouseY);

	InputManager myInput = InputManager();
	myInput.CreateVirtualButton();
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) )
	{
		screen.Refresh();
		myScene.Update(screen.ElapsedTime());
	}

	rm.FreeResources();

	return 0;
}

/*
	Screen& screen = Screen::Instance();
	const Renderer& render = Renderer::Instance();
	ResourceManager& rm = ResourceManager::Instance();

	screen.Open(screenX, screenY, false);
	screen.Refresh();
	render.SetBlendMode(Renderer::BlendMode::ALPHA);

	Image* backLayer = rm.LoadImage("data/backlayer.png");
	Image* frontLayer = rm.LoadImage("data/frontlayer.png");
	ParallaxScene myScene = ParallaxScene(backLayer, frontLayer);
	myScene.SetAutoBackSpeed(backMoveX, backMoveY);
	myScene.SetAutoFrontSpeed(frontMoveX, frontMoveY);
	myScene.SetRelativeBackSpeed(backRelX, backRelY);
	myScene.SetRelativeFrontSpeed(frontRelX, frontRelY);

	Image* alien = rm.LoadImage("data/alien.png");
	Sprite* myAlien = myScene.CreateSprite(alien);
	myAlien->SetPosition(midScreenX, midScreenY);
	myScene.GetCamera().FollowSprite(myAlien);
	double xAlien = myAlien->GetX();
	double yAlien = myAlien->GetY();

	InputManager myInput = InputManager();
	myInput.CreateVirtualButton(UP, Key_W);
	myInput.CreateVirtualButton(DOWN, Key_S);
	myInput.CreateVirtualButton(LEFT, Key_A);
	myInput.CreateVirtualButton(RIGHT, Key_D);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) )
	{
		// Actualizamos la pantalla, la escena y la entrada.
		screen.Refresh();
		myScene.Update(screen.ElapsedTime());
		myInput.Update();

		// Actualizamos movimiento.
		xAlien = myAlien->GetX();
		yAlien = myAlien->GetY();
		if (myInput.IsVirtualButtonPressed(UP) && myInput.IsVirtualButtonPressed(RIGHT))
		{
			myAlien->MoveTo(xAlien + moveSpeed, yAlien - moveSpeed, moveSpeed);
			myAlien->RotateTo(-spriteAngle, angleSpeed);
		}
		else if (myInput.IsVirtualButtonPressed(UP) && myInput.IsVirtualButtonPressed(LEFT))
		{
			myAlien->MoveTo(xAlien - moveSpeed, yAlien - moveSpeed, moveSpeed);
			myAlien->RotateTo(spriteAngle, angleSpeed);
		}
		else if (myInput.IsVirtualButtonPressed(DOWN) && myInput.IsVirtualButtonPressed(RIGHT))
		{
			myAlien->MoveTo(xAlien + moveSpeed, yAlien + moveSpeed, moveSpeed);
			myAlien->RotateTo(-spriteAngle, angleSpeed);
		}
		else if (myInput.IsVirtualButtonPressed(DOWN) && myInput.IsVirtualButtonPressed(LEFT))
		{
			myAlien->MoveTo(xAlien - moveSpeed, yAlien + moveSpeed, moveSpeed);
			myAlien->RotateTo(spriteAngle, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(UP))
		{
			myAlien->MoveTo(xAlien, yAlien - moveSpeed, moveSpeed);
			myAlien->RotateTo(0, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(DOWN))
		{
			myAlien->MoveTo(xAlien, yAlien + moveSpeed, moveSpeed);
			myAlien->RotateTo(0, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(LEFT))
		{
			myAlien->MoveTo(xAlien - moveSpeed, yAlien, moveSpeed);
			myAlien->RotateTo(spriteAngle, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(RIGHT))
		{
			myAlien->MoveTo(xAlien + moveSpeed, yAlien, moveSpeed);
			myAlien->RotateTo(-spriteAngle, angleSpeed);
		}
		else
		{
			myAlien->MoveTo(xAlien, yAlien, moveSpeed);
			myAlien->RotateTo(0, angleSpeed);
		}

		// Mostramos por pantalla.
		myScene.Render();
	}

	rm.FreeResources();
	return 0;
}
*/
