#include "../include/sprite.h"
//#include "../include/rectcollision.h"
#include "../include/image.h"
//#include "../include/map.h"
#include "../include/math.h"
//#include "../include/pixelcollision.h"
#include "../include/renderer.h"
//#include "../include/circlecollision.h"
#include <math.h>

Sprite::Sprite(Image* image) {
	// TAREA: Implementar
	this->image = image;
	this->image->SetMidHandle();
	x = y = z = 0;
	colx = coly = 0;
	colwidth = image->GetWidth();
	colheight = image->GetHeight();
	angle = 0;
	scalex = scaley = 1;
	radius = 0;
	animFPS = 0;
	firstFrame = lastFrame = 0;
	currentFrame = 0;
	blendMode = Renderer::BlendMode::SOLID;
	r = g = b = 0;
	a = 255;
	collision = NULL;
	colPixelData = NULL;
	colSprite = NULL;
	collided = false;

	rotating = false;
	toAngle = 0;
	rotatingSpeed = 0;
	anglesToRotate = 0;

	moving = false;
	toX = toY = 0;
	movingSpeedX = movingSpeedY = 0;
	prevX = prevY = 0;
}

Sprite::~Sprite() {
    // TAREA: Implementar
}

void Sprite::SetCollision(CollisionMode mode) {
	// TAREA: Implementar
}
/*
bool Sprite::CheckCollision(Sprite* sprite) {
	// TAREA: Implementar
}

bool Sprite::CheckCollision(const Map* map) {
	// TAREA: Implementar
}
*/
void Sprite::RotateTo(int32 angle, double speed) {
	// TAREA: Implementar
	toAngle = WrapValue(angle, 360);
	if (toAngle - this->angle < this->angle - toAngle)
	{
		anglesToRotate = WrapValue(toAngle - this->angle, 360);
		rotatingSpeed = speed;
	}
	else
	{
		anglesToRotate = WrapValue(this->angle - toAngle, 360);
		rotatingSpeed = -speed;
	}
	rotating = true;
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar
	toX = x;
	toY = y;
	prevX = this->x;
	prevY = this->y;
	movingSpeedX = speedX;
	if (speedY == 0)
	{
		double time = toX / movingSpeedX;
		movingSpeedY = toY / time;
	}
	else
		movingSpeedY = speedY;
	moving = true;
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	// TAREA: Actualizar rotacion animada
	if (rotating)
	{
		angle = WrapValue(angle + rotatingSpeed * elapsed, 360);
		if (abs(toAngle - angle) > 0)
			rotating = false;
	}
	else
		rotating = false;

	// TAREA: Actualizar movimiento animado
	if (moving)
	{
		x = x + movingSpeedX * elapsed;
		y = y + movingSpeedY * elapsed;
		if (x == toX && y == toY)
			moving = false;
	}
	else
		moving = false;

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
    // TAREA: Implementar
	Renderer::Instance().SetBlendMode(blendMode);
	Renderer::Instance().DrawImage(image, x, y, 0, colwidth * scalex, colheight * scaley, angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
