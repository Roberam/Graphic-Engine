#include "../include/parallaxscene.h"
#include "../include/image.h"
#include "../include/screen.h"

#define sWidth Screen::Instance().GetWidth()
#define sHeight Screen::Instance().GetHeight()

ParallaxScene::ParallaxScene(Image* imageBack, Image* imageFron)
{
	backLayer = NULL;
	frontLayer = NULL;
	backLayer = imageBack;
	frontLayer = imageFron;
	backX = backY = frontX = frontY = 0;
	SetRelativeBackSpeed(1, 1);
	SetRelativeFrontSpeed(1, 1);
	SetAutoBackSpeed(0, 0);
	SetAutoFrontSpeed(0, 0);
}

const Image* ParallaxScene::GetBackLayer() const
{
	return backLayer;
}

const Image* ParallaxScene::GetFrontLayer() const
{
	return frontLayer;
}

void ParallaxScene::SetRelativeBackSpeed(double x, double y)
{
	relBackSpeedX = x;
	relBackSpeedY = y;
}

void ParallaxScene::SetRelativeFrontSpeed(double x, double y)
{
	relFrontSpeedX = x;
	relFrontSpeedY = y;
}

void ParallaxScene::SetAutoBackSpeed(double x, double y)
{
	autoBackSpeedX = x;
	autoBackSpeedY = y;
}

void ParallaxScene::SetAutoFrontSpeed(double x, double y)
{
	autoFrontSpeedX = x;
	autoFrontSpeedY = y;
}

void ParallaxScene::Update(double elapsed, Map* map)
{
	Scene::Update(elapsed, map);

	if (backLayer)
	{
		backX = backX - autoBackSpeedX * elapsed;
		backY = backY - autoBackSpeedY * elapsed;
	}
	if (frontLayer)
	{
		frontX = frontX - autoFrontSpeedX * elapsed;
		frontY = frontY - autoFrontSpeedY * elapsed;
	}
}

void ParallaxScene::RenderBackground() const
{
	Scene::RenderBackground();

	Renderer::Instance().SetBlendMode(Renderer::BlendMode::ALPHA);
	Renderer::Instance().SetColor(255, 255, 255, 255);
	if (backLayer)
	{
		double xPos = backX + relBackSpeedX * GetCamera().GetX();
		double yPos = backY + relBackSpeedY * GetCamera().GetY();
		Renderer::Instance().DrawTiledImage(backLayer, 0, 0, sWidth, sHeight, xPos, yPos);
	}
	if (frontLayer)
	{
		double xPos = frontX + relFrontSpeedX * GetCamera().GetX();
		double yPos = frontY + relFrontSpeedY * GetCamera().GetY();
		Renderer::Instance().DrawTiledImage(frontLayer, 0, 0, sWidth, sHeight, xPos, yPos);
	}
}
