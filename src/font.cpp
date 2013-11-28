#include "../include/font.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include "../include/renderer.h"

Font::Font(const String& filename) : Image(filename, 16, 16)
{
}

uint16 Font::GetSize() const
{
	return Image::GetHeight();
}

uint32 Font::GetTextWidth(const String& text) const
{
	return text.Length() * Image::GetWidth();
}

uint32 Font::GetTextHeight(const String& text) const
{
	return Image::GetHeight();
}

void Font::Render(const String& text, double x, double y) const
{
	uint16 length = text.Length();
	uint16 offset = 0;
	for (uint16 i = 0; i < length; i++)
	{
		Renderer::Instance().DrawImage(this, x + offset, y, text[i], Image::GetWidth(), Image::GetHeight());
		offset = offset + Image::GetWidth();
	}
}
