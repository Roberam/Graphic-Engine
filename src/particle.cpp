#include "../include/particle.h"
#include "../include/sprite.h"
#include "../include/image.h"

const double alphaTotal = 255;

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
	MoveTo(GetX() + velocityx, GetY() + velocityy, velocityx, velocityy);
	RotateTo(GetAngle() + angularVelocity, angularVelocity);
	Sprite::Update(elapsed);
	lifetime = lifetime - elapsed;
	if (autofade)
		SetColor(GetRed(), GetGreen(), GetBlue(), alphaTotal * lifetime / initialLifetime);
}
