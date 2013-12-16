#include "../include/glyph.h"

Glyph::Glyph(const uint32 iniX, const uint32 iniY, const uint32 finX, const uint32 finY)
{
	_iniX = iniX;
	_iniY = iniY;
	_finX = finX;
	_finY = finY;
}

uint32 Glyph::GetIniX() const
{
	return _iniX;
}

uint32 Glyph::GetIniY() const
{
	return _iniY;
}

uint32 Glyph::GetFinX() const
{
	return _finX;
}

uint32 Glyph::GetFinY() const
{
	return _finY;
}

void Glyph::SetIni(const uint32 x, const uint32 y)
{
	_iniX = x;
	_iniY = y;
}

void Glyph::SetFin(const uint32 x, const uint32 y)
{
	_finX = x;
	_finY = y;
}
