#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/InputManager.h"

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 midScreenX = screenX / 2;
const uint16 midScreenY = screenY / 2;

const int16 moveSpeed = 256;
const int32 spriteAngle = 15;
const double angleSpeed = 30;

const String UP = "ARRIBA";
const String DOWN = "ABAJO";
const String LEFT = "IZQUIERDA";
const String RIGHT = "DERECHA";

uint16 Random(const uint16 min, const uint16 max)
{
	return (uint16)(min + (max - min) * (float)rand() / RAND_MAX);
}

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(screenX, screenY, false);
	screen.Refresh();
	
	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	Image* myBackground = ResourceManager::Instance().LoadImage("data/background.png");
	Scene myScene;
	myScene.SetBackgroundImage(myBackground);

	Image* myAlien = ResourceManager::Instance().LoadImage("data/alien.png");
	Sprite* myAlienSprite = myScene.CreateSprite(myAlien);
	myAlienSprite->SetPosition(midScreenX, midScreenY);

	Camera* myCamera = &myScene.GetCamera();
	myCamera->SetBounds(0, 0, myBackground->GetWidth(), myBackground->GetHeight());
	myCamera->FollowSprite(myAlienSprite);

	InputManager myInput = InputManager();
	myInput.CreateVirtualButton(UP, Key_W);
	myInput.CreateVirtualButton(DOWN, Key_S);
	myInput.CreateVirtualButton(LEFT, Key_A);
	myInput.CreateVirtualButton(RIGHT, Key_D);

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) )
	{
		// Actualizamos la pantalla, la escena, el sprite y la entrada.
		screen.Refresh();
		myScene.Update(screen.ElapsedTime());
		myInput.Update();

		// Actualizamos movimiento.
		double xAlien = myAlienSprite->GetX();
		double yAlien = myAlienSprite->GetY();
		if (myInput.IsVirtualButtonPressed(UP) && myInput.IsVirtualButtonPressed(RIGHT))
		{
			myAlienSprite->MoveTo(xAlien + moveSpeed, yAlien - moveSpeed, moveSpeed);
			myAlienSprite->RotateTo(-spriteAngle, angleSpeed);
		}
		else if (myInput.IsVirtualButtonPressed(UP) && myInput.IsVirtualButtonPressed(LEFT))
		{
			myAlienSprite->MoveTo(xAlien - moveSpeed, yAlien - moveSpeed, moveSpeed);
			myAlienSprite->RotateTo(spriteAngle, angleSpeed);
		}
		else if (myInput.IsVirtualButtonPressed(DOWN) && myInput.IsVirtualButtonPressed(RIGHT))
		{
			myAlienSprite->MoveTo(xAlien + moveSpeed, yAlien + moveSpeed, moveSpeed);
			myAlienSprite->RotateTo(-spriteAngle, angleSpeed);
		}
		else if (myInput.IsVirtualButtonPressed(DOWN) && myInput.IsVirtualButtonPressed(LEFT))
		{
			myAlienSprite->MoveTo(xAlien - moveSpeed, yAlien + moveSpeed, moveSpeed);
			myAlienSprite->RotateTo(spriteAngle, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(UP))
		{
			myAlienSprite->MoveTo(xAlien, yAlien - moveSpeed, moveSpeed);
			myAlienSprite->RotateTo(0, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(DOWN))
		{
			myAlienSprite->MoveTo(xAlien, yAlien + moveSpeed, moveSpeed);
			myAlienSprite->RotateTo(0, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(LEFT))
		{
			myAlienSprite->MoveTo(xAlien - moveSpeed, yAlien, moveSpeed);
			myAlienSprite->RotateTo(spriteAngle, angleSpeed);
		}
		else if(myInput.IsVirtualButtonPressed(RIGHT))
		{
			myAlienSprite->MoveTo(xAlien + moveSpeed, yAlien, moveSpeed);
			myAlienSprite->RotateTo(-spriteAngle, angleSpeed);
		}
		else
		{
			myAlienSprite->MoveTo(xAlien, yAlien, moveSpeed);
			myAlienSprite->RotateTo(0, angleSpeed);
		}

		// Mostramos por pantalla.
		myScene.Render();
	}

	ResourceManager::Instance().FreeResources();
	return 0;
}





/*
	Font* myImageFont = ResourceManager::Instance().LoadFont("data/arial16.png");
	//Font* myImageFont = ResourceManager::Instance().LoadFont("data/monospaced.png");
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
			uint8 r = (uint8)Random(colorMin, colorMax);
			uint8 g = (uint8)Random(colorMin, colorMax);
			uint8 b = (uint8)Random(colorMin, colorMax);
			Renderer::Instance().SetColor(r, g, b, alpha);
			collides = false;
		}
		Renderer::Instance().DrawText(myImageFont, text, posX, posY);
	}

	ResourceManager::Instance().FreeResources();
	return 0;
}
*/
