#ifndef _AFFECTOR_H_
#define _AFFECTOR_H_

#include "types.h"
#include "particle.h"

enum AffectorMode
{
	ALL_ENABLE = 0,
	VELOCITY = 1,
	ANG_VEL = 2,
	COLOR = 4
};

class Affector
{
public:
	Affector(const uint8 mode = ALL_ENABLE);
	~Affector();

	virtual void SetRange(const double x0, const double y0, const double x1, const double y1);
	virtual void SetVelocityX(const double minvelx, const double maxvelx);
	virtual void SetVelocityY(const double minvely, const double maxvely);
	virtual void SetAngularVelocity(const double minvelang, const double maxvelang);
	virtual void SetMinColor(const uint8 r, const uint8 g, const uint8 b);
	virtual void SetMaxColor(const uint8 r, const uint8 g, const uint8 b);

	virtual double GetVelocityX() const;
	virtual double GetVelocityY() const;
	virtual double GetAngularVelocity() const;
	virtual uint8 GetRed() const;
	virtual uint8 GetGreen() const;
	virtual uint8 GetBlue() const;

	virtual bool InRange(const double x, const double y) const;
	virtual void AddAffected(Particle* p);
	virtual void RemoveAffected(Particle* p);
	virtual bool IsAffecting(Particle* p) const;

	virtual uint8 GetMode() const { return mode; }
private:
	double x0, y0, x1, y1;
	uint8 minr, maxr;
	uint8 ming, maxg;
	uint8 minb, maxb;
	double minvelx, maxvelx;
	double minvely, maxvely;
	double minvelang, maxvelang;

	Array<Particle*> affected;
	uint8 mode;
};

#endif
