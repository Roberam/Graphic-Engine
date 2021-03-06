#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"
#include "include/InputManager.h"

const uint16 screenX = 800;
const uint16 screenY = 600;
const uint16 midScreenX = screenX / 2;
const uint16 midScreenY = screenY / 2;
const bool fullscreen = false;

const double rateMin = 500;
const double rateMax = 1000;
const double velMin = -128;
const double velMax = 128;
const double velAngMin = 0;
const double velAngMax = 360;
const double timeLifeMin = 1;
const double timeLifeMax = 2;
const uint8 colorMin = 0;
const uint8 colorMax = 255;
const bool autofade = true;

const uint8 modeLeft = AffectorMode::ANG_VEL + AffectorMode::COLOR;
const uint8 minRedLeft = 0;
const uint8 minGreenLeft = 0;
const uint8 minBlueLeft = 0;
const uint8 maxRedLeft = 255;
const uint8 maxGreenLeft = 255;
const uint8 maxBlueLeft = 0;
const double minvelangLeft = 0;
const double maxvelangLeft = 360;

const uint8 modeRight = AffectorMode::ANG_VEL + AffectorMode::COLOR;
const uint8 minRedRight = 0;
const uint8 minGreenRight = 0;
const uint8 minBlueRight = 0;
const uint8 maxRedRight = 0;
const uint8 maxGreenRight = 255;
const uint8 maxBlueRight = 255;
const double minvelangRight = 360;
const double maxvelangRight = 720;

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	const Renderer& render = Renderer::Instance();
	ResourceManager& rm = ResourceManager::Instance();
	
	screen.Refresh();
	screen.Open(screenX, screenY, fullscreen);
	render.SetBlendMode(Renderer::BlendMode::ALPHA);

	Scene myScene = Scene();
	Image* myImage = rm.LoadImage("data/star.png");
	myImage->SetMidHandle();
	Sprite* mySprite = myScene.CreateSprite(myImage);
	int mouseX = midScreenX;
	int mouseY = midScreenY;
	glfwSetMousePos(mouseX, mouseY);
	mySprite->SetPosition((double)mouseX, (double)mouseY);
	glfwDisable(GLFW_MOUSE_CURSOR);

	Emitter* myEmitter = myScene.CreateEmitter(myImage, autofade);
	myEmitter->SetAngularVelocity(velAngMin, velAngMax);
	myEmitter->SetBlendMode(Renderer::BlendMode::ADDITIVE);
	myEmitter->SetLifetime(timeLifeMin, timeLifeMax);
	myEmitter->SetMaxColor(colorMax, colorMax, colorMax);
	myEmitter->SetMinColor(colorMin, colorMin, colorMin);
	myEmitter->SetPosition((double)mouseX, (double)mouseY);
	myEmitter->SetRate(rateMin, rateMax);
	myEmitter->SetVelocityX(velMin, velMax);
	myEmitter->SetVelocityY(velMin, velMax);

	Affector* affectorLeft = myEmitter->CreateAffector(modeLeft);
	affectorLeft->SetAngularVelocity(minvelangLeft, maxvelangLeft);
	affectorLeft->SetMaxColor(maxRedLeft, maxGreenLeft, maxBlueLeft);
	affectorLeft->SetMinColor(minRedLeft, minGreenLeft, minBlueLeft);
	affectorLeft->SetRange(0, 0, midScreenX, screenY);
	
	Affector* affectorRight = myEmitter->CreateAffector(modeRight);
	affectorRight->SetAngularVelocity(minvelangRight, maxvelangRight);
	affectorRight->SetMaxColor(maxRedRight, maxGreenRight, maxBlueRight);
	affectorRight->SetMinColor(minRedRight, minGreenRight, minBlueRight);
	affectorRight->SetRange(midScreenX + 1, 0, screenX, screenY);
	
	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC) )
	{
		// Actualizamos la pantalla y la escena.
		screen.Refresh();
		myScene.Update(screen.ElapsedTime());

		// Actualizamos los movimientos.
		mouseX = screen.GetMouseX();
		mouseY = screen.GetMouseY();
		mySprite->SetPosition(mouseX, mouseY);
		myEmitter->SetPosition(mouseX, mouseY);
		if ( screen.MouseButtonPressed(GLFW_MOUSE_BUTTON_LEFT) )
			myEmitter->Start();
		else
			myEmitter->Stop();

		// Mostramos por pantalla.
		myScene.Render();

	}

	rm.FreeResources();

	return 0;
}
