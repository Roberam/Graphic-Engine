#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#include "sprite.h"
#include "image.h"

class Particle : public Sprite
{
public:
	Particle();
	Particle(Image* image, double velx, double vely, double angularVel, double lifetime, bool autofade);

	virtual double GetLifetime() const;

	virtual void Update(double elapsed);
private:
	double velocityx, velocityy;
	double angularVelocity;
	double lifetime;
	double initialLifetime;
	bool autofade;
};

#endif
