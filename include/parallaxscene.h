#ifndef _PARALLAXSCENE_H_
#define _PARALLAXSCENE_H_

#include "scene.h"
#include "image.h"

class ParallaxScene : public Scene
{
public:
	ParallaxScene(Image* imageBack, Image* imageFront = 0);

	virtual const Image* GetBackLayer() const;
	virtual const Image* GetFrontLayer() const;
	virtual void SetRelativeBackSpeed(double x, double y);
	virtual void SetRelativeFrontSpeed(double x, double y);
	virtual void SetAutoBackSpeed(double x, double y);
	virtual void SetAutoFrontSpeed(double x, double y);

	virtual void Update(double elapsed, Map* map = 0);
protected:
	virtual void RenderBackground() const;
private:
	Image* backLayer;
	Image* frontLayer;
	double backX, backY;
	double frontX, frontY;
	double relBackSpeedX, relBackSpeedY;
	double relFrontSpeedX, relFrontSpeedY;
	double autoBackSpeedX, autoBackSpeedY;
	double autoFrontSpeedX, autoFrontSpeedY;
};

#endif
