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
	firstFrame = lastFrame = currentFrame = (double)0;
	blendMode = Renderer::BlendMode::SOLID;
	r = g = b = a = 0;
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
	/*if (!rotating)
	{
		rotatingSpeed = speed;
		anglesToRotate = abs(toAngle - this->angle);
		if (toAngle - this->angle < this->angle - toAngle)
			toAngle = angle;
		else
			toAngle = -angle;
		rotating = true;
	}*/
}

void Sprite::MoveTo(double x, double y, double speedX, double speedY) {
	// TAREA: Implementar
}

void Sprite::Update(double elapsed, const Map* map) {
	// Informacion inicial de colision
	colSprite = NULL;
	collided = false;

	// TAREA: Actualizar animacion

	// TAREA: Actualizar rotacion animada
	/*if (anglesToRotate > 0)
	{
		angle = angle + toAngle * rotatingSpeed * elapsed;
		anglesToRotate = anglesToRotate - anglesToRotate * elapsed;
	}
	else
		rotating = false;*/

	// TAREA: Actualizar movimiento animado

	// Informacion final de colision
	UpdateCollisionBox();
}

void Sprite::Render() const {
    // TAREA: Implementar
	Renderer::Instance().DrawImage(image, x, y, 0, colwidth * scalex, colheight * scaley, angle);
}

void Sprite::UpdateCollisionBox() {
	// TAREA: Implementar
}

void Sprite::UpdateCollisionBox(double x, double y, double w, double h) {
	// TAREA: Implementar
}
