#ifndef UGINE_GLYPH_H
#define UGINE_GLYPH_H

#include "types.h"

class Glyph
{
public:
	Glyph(const uint32 iniX = 0, const uint32 iniY = 0, const uint32 finX = 0, const uint32 finY = 0);
	
	uint32 GetIniX() const;
	uint32 GetIniY() const;
	uint32 GetFinX() const;
	uint32 GetFinY() const;

	void SetIni(const uint32 x, const uint32 y);
	void SetFin(const uint32 x, const uint32 y);
private:
	uint32 _iniX;
	uint32 _iniY;
	uint32 _finX;
	uint32 _finY;
};

#endif
