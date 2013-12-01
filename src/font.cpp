#include "../include/font.h"
#include "../include/types.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include "../include/renderer.h"
#include "../include/array.h"
#include "../include/string.h"
#include "../include/glyph.h"
#include "../include/image.h"
#include <stdlib.h>

const int nElemPixel = 4;
const int nFrameX = 16;
const int nFrameY = 16;
const int dimFrameX = 32;
const int dimFrameY = 32;

int IndexFrom(int i, int j, int k, int l, int width, int c)
{
	return ( i * dimFrameX + k + ( j * dimFrameY + l ) * width ) * nElemPixel + c;
}

bool IsColor(uint8 r0, uint8 g0, uint8 b0, uint8 r1, uint8 g1, uint8 b1)
{
	return r0 == r1 && g0 == g1 && b0 == b1;
}

extern "C" unsigned char* stbi_load(const char* filename, int* x, int* y, int* comp, int req_comp);

Font::Font(const String& filename) : Image(filename, 16, 16)
{
	_glyphs = Array<Glyph>();
	Glyph myGlyph = Glyph();

	// Cargamos el buffer con la imagen
	int iWidth;
	int iHeight;
	unsigned char* buffer = stbi_load(filename.ToCString(), &iWidth, &iHeight, NULL, nElemPixel);

	// Tratamos los pixeles dentro de cada frame
	if ( buffer ) {
		for (int j = 0; j < nFrameY; j++)
		{
			for (int i = 0; i < nFrameX; i++)
			{
				// Accedemos al frame[i,j]
				for (int k = 0; k < dimFrameX; k++)
				{
					for (int l = 0; l < dimFrameY; l++)
					{
						// Accedemos al pixel[k,l] del frame[i,j]
						uint8 r = buffer[IndexFrom(i, j, k, l, iWidth, 0)];
						uint8 g = buffer[IndexFrom(i, j, k, l, iWidth, 1)];
						uint8 b = buffer[IndexFrom(i, j, k, l, iWidth, 2)];
						if (IsColor(r, g, b, 255, 255, 0))
						{
							myGlyph.SetIni(i * dimFrameX + k, j * dimFrameY + l);
							buffer[IndexFrom(i, j, k, l, iWidth, 3)] = 0;
						}
						else if (IsColor(r, g, b, 255, 0, 0))
						{
							myGlyph.SetFin(i * dimFrameX + k, j * dimFrameY + l);
							buffer[IndexFrom(i, j, k, l, iWidth, 3)] = 0;
						}
						else if (IsColor(r, g, b, 0, 0, 0))
						{
							buffer[IndexFrom(i, j, k, l, iWidth, 3)] = 0;
						}
					}
				}
				_glyphs.Add(myGlyph);
			}
		}
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iWidth, iHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		free(buffer);
	}
}

Font::~Font()
{
}

uint16 Font::GetSize() const
{
	return Image::GetHeight();
}

uint32 Font::GetTextWidth(const String& text) const
{
	uint32 width = 0;

	for (int i = 0; i < text.Length(); i++)
		width = width + _glyphs[text[i]].GetFinX() - _glyphs[text[i]].GetIniX();

	return width;
}

uint32 Font::GetTextHeight(const String& text) const
{
	uint32 height = 0;

	for (int i = 0; i < text.Length(); i++)
	{
		uint32 newHeight = _glyphs[text[i]].GetFinY() - _glyphs[text[i]].GetIniY();
		if (height <= newHeight)
			height = newHeight;
	}

	return height;
}

void Font::Render(const String& text, double x, double y) const
{
	uint16 length = text.Length();
	uint16 offset = 0;
	for (uint16 i = 0; i < length; i++)
	{
		Renderer::Instance().DrawImage(this, x + offset, y, text[i], Image::GetWidth(), Image::GetHeight());
		offset = offset + _glyphs[text[i]].GetFinX() - _glyphs[text[i]].GetIniX();
	}
}
