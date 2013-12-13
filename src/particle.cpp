#include "../include/particle.h"
#include "../include/sprite.h"
#include "../include/image.h"

Particle::Particle() : Sprite(NULL)
{
	velocityx = velocityy = 0;
	angularVelocity = 0;
	lifetime = initialLifetime = 0;
	autofade = false;
}

Particle::Particle(Image* image, double velx, double vely, double angularVel,
				   double lifetime, bool autofade) : Sprite(image)
{
	velocityx = velx;
	velocityy = vely;
	angularVelocity = angularVel;
	this->lifetime = lifetime;
	initialLifetime = lifetime;
	this->autofade = autofade;
}

double Particle::GetLifetime() const
{
	return lifetime;
}

void Particle::Update(double elapsed)
{
	SetX(GetX() + velocityx * elapsed);
	SetY(GetY() + velocityy * elapsed);
	SetAngle(GetAngle() + angularVelocity * elapsed);
	lifetime = lifetime - elapsed;

	if (lifetime <= 0)
		lifetime = 0;

	if (autofade)
		Sprite::SetColor(GetRed(), GetGreen(), GetBlue(), (uint8)(255 * lifetime/initialLifetime));
}

void Particle::SetVelocity(double velx, double vely)
{
	velocityx = velx;
	velocityy = vely;
}

void Particle::SetAngVelocity(double angVelocity)
{
	angularVelocity = angVelocity;
}
