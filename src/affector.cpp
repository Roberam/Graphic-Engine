#include "../include/affector.h"
#include "../include/types.h"
#include "../include/math.h"
#include "../include/particle.h"
#include "../include/image.h"

Affector::Affector()
{
	x0 = y0 = x1 = y1 = 0;
	minr = ming = minb = 0;
	maxr = maxg = maxb = 0;
	minvelx = maxvelx = minvely = maxvely = 0;
	minvelang = maxvelang = 0;

	affected = Array<Particle*>();
}

Affector::~Affector()
{
}

void Affector::SetRange(const double x0, const double y0, const double x1, const double y1)
{
	if (x0 <= x1 && y0 <= y1)
	{
		this->x0 = x0;
		this->y0 = y0;
		this->x1 = x1;
		this->y1 = y1;
	}
}

void Affector::SetVelocityX(const double minvelx, const double maxvelx)
{
	if (minvelx <= maxvelx)
	{
		this->minvelx = minvelx;
		this->maxvelx = maxvelx;
	}
}

void Affector::SetVelocityY(const double minvely, const double maxvely)
{
	if (minvely <= maxvely)
	{
		this->minvely = minvely;
		this->maxvely = maxvely;
	}
}

void Affector::SetAngularVelocity(const double minvelang, const double maxvelang)
{
	if (minvelang <= maxvelang)
	{
		this->minvelang = minvelang;
		this->maxvelang = maxvelang;
	}
}

void Affector::SetMinColor(const uint8 r, const uint8 g, const uint8 b)
{
	minr = r;
	ming = g;
	minb = b;
}

void Affector::SetMaxColor(const uint8 r, const uint8 g, const uint8 b)
{
	maxr = r;
	maxg = g;
	maxb = b;
}

double Affector::GetVelocityX() const
{
	return Random(minvelx, maxvelx);
}

double Affector::GetVelocityY() const
{
	return Random(minvely, maxvely);
}

double Affector::GetAngularVelocity() const
{
	return Random(minvelang, maxvelang);
}

uint8 Affector::GetRed() const
{
	return (uint8)Random(minr, maxr);
}

uint8 Affector::GetGreen() const
{
	return (uint8)Random(ming, maxg);
}

uint8 Affector::GetBlue() const
{
	return (uint8)Random(minb, maxb);
}

bool Affector::InRange(const double x, const double y) const
{
	return x0 <= x && x <= x1 && y0 <= y && y <= y1;
}

void Affector::AddAffected(Particle* p)
{
	if (!IsAffecting(p))
		affected.Add(p);
}

void Affector::RemoveAffected(Particle* p)
{
	affected.Remove(p);
}

bool Affector::IsAffecting(Particle* p) const
{
	bool found = false;
	uint32 i = 0;

	while (!found && i < affected.Size())
	{
		if (affected[i] == p)
			found = true;
		else
			i++;
	}

	return found;
}
