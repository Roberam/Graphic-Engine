#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

#include "include/u-gine.h"

const double dimImage = 64;
const double iniX = 10;
const double iniY = 10;
const int numModes = 6;
GLenum modesX[numModes] = {GL_ZERO, GL_ONE, GL_DST_COLOR, GL_ONE_MINUS_DST_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};
GLenum modesY[numModes] = {GL_ZERO, GL_ONE, GL_SRC_COLOR, GL_ONE_MINUS_SRC_COLOR, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA};

int main(int argc, char* argv[]) {
	Screen& screen = Screen::Instance();
	screen.Open(800, 600, false);
	Image* imageWall = ResourceManager::Instance().LoadImage("data/box.jpg");
	Image* imageLight = ResourceManager::Instance().LoadImage("data/light.png");

	while ( screen.IsOpened() && !screen.KeyPressed(GLFW_KEY_ESC))
	{
		Renderer::Instance().SetBlendMode(Renderer::BlendMode::SOLID);
		Renderer::Instance().Clear(0, 0, 0);
		for (int i = 0; i < numModes; i++)
		{
			for (int j = 0; j < numModes; j++)
			{
				Renderer::Instance().SetBlendMode(Renderer::BlendMode::SOLID);
				Renderer::Instance().DrawImage(imageWall, i*dimImage + iniX, j*dimImage + iniY, 0, dimImage, dimImage, 0);
				glBlendFunc(modesX[i], modesY[j]);
				Renderer::Instance().DrawImage(imageLight, i*dimImage + iniX, j*dimImage + iniY, 0, dimImage, dimImage, 0);
			}
		}

		// Refrescamos la pantalla
		screen.Refresh();
	}

	ResourceManager::Instance().FreeResources();
	
	return 0;
}
