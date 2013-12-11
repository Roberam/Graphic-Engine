#include "../include/emitter.h"
#include "../include/image.h"
#include "../include/types.h"
#include "../include/renderer.h"
#include "../include/array.h"
#include "../include/math.h"

Emitter::Emitter(Image* image, bool autofade)
{
	this->image = image;
	this->image->SetMidHandle();
	this->autofade = autofade;
	x = y = 0;
	minrate = maxrate = 0;
	minvelx = maxvelx = 0;
	minvely = maxvely = 0;
	minangvel = maxangvel = 0;
	minlifetime = maxlifetime = 0;
	minr = ming = minb = 0;
	maxr = maxg = maxb = 0;
	blendMode = Renderer::BlendMode::ALPHA;
	emitting = false;
	particles = Array<Particle>();
}

void Emitter::SetPosition(double x, double y)
{
	this->x = x;
	this->y = y;
}

void Emitter::SetX(double x)
{
	this->x = x;
}

void Emitter::SetY(double y)
{
	this->y = y;
}

double Emitter::GetX() const
{
	return x;
}

double Emitter::GetY() const
{
	return y;
}

void Emitter::SetRate(double minrate, double maxrate)
{
	if (minrate <= maxrate)
	{
		this->minrate = minrate;
		this->maxrate = maxrate;
	}
}

void Emitter::SetVelocityX(double minvelx, double maxvelx)
{
	if (minvelx <= maxvelx)
	{
		this->minvelx = minvelx;
		this->maxvelx = maxvelx;
	}
}

void Emitter::SetVelocityY(double minvely, double maxvely)
{
	if (minvely <= maxvely)
	{
		this->minvely = minvely;
		this->maxvely = maxvely;
	}
}

void Emitter::SetAngularVelocity(double minangvel, double maxangvel)
{
	if (minangvel <= maxangvel)
	{
		this->minangvel = minangvel;
		this->maxangvel = maxangvel;
	}
}

void Emitter::SetLifetime(double minlifetime, double maxlifetime)
{
	if (minlifetime <= maxlifetime)
	{
		this->minlifetime = minlifetime;
		this->maxlifetime = maxlifetime;
	}
}

void Emitter::SetMinColor(uint8 r, uint8 g, uint8 b)
{
	minr = r;
	ming = g;
	minb = b;
}

void Emitter::SetMaxColor(uint8 r, uint8 g, uint8 b)
{
	maxr = r;
	maxg = g;
	maxb = b;
}

void Emitter::SetBlendMode(Renderer::BlendMode mode)
{
	blendMode = mode;
}

void Emitter::Start()
{
	emitting = true;
}

void Emitter::Stop()
{
	emitting = false;
}

bool Emitter::IsEmitting() const
{
	return emitting;
}

void Emitter::Update(double elapsed)
{
	Array<uint32> toDelete = Array<uint32>();

	if (emitting)
	{
		uint8 r = 0, g = 0, b = 0;
		double velx = 0, vely = 0;
		double angvel = 0;
		double lifetime = 0;

		// Incrementamos la lista de particulas.
		uint32 rate = (uint32)(Random(minrate, maxrate) * elapsed);
		for (uint32 i = 0; i < rate; i++)
		{
			r = (uint8)Random(minr, maxr);
			g = (uint8)Random(ming, maxg);
			b = (uint8)Random(minb, maxb);
			velx = Random(minvelx, maxvelx);
			vely = Random(minvely, maxvely);
			angvel = Random(minangvel, maxangvel);
			lifetime = Random(minlifetime, maxlifetime);
			Particle p = Particle(image, velx, vely, angvel, lifetime, autofade);
			p.SetBlendMode(blendMode);
			p.SetColor(r, g, b);
			p.SetPosition(x, y);
			particles.Add(p);
		}
	}

	// Actualizamos la lista de particulas.
	for (uint32 i = 0; i < particles.Size(); i++)
	{
		particles[i].Update(elapsed);
		if (particles[i].GetLifetime() <= 0)
			toDelete.Add(i);
	}

	// Eliminamos las particulas cuyo lifetime haya expirado.
	for (uint32 i = 0; i < toDelete.Size(); i++)
		particles.RemoveAt(toDelete[i]);
}

void Emitter::Render() const
{
	Renderer::Instance().SetBlendMode(blendMode);
	for (uint32 i = 0; i < particles.Size(); i++)
		particles[i].Render();
}
