#include "../include/image.h"
#include "../include/glinclude.h"
#include "../include/math.h"
#include <math.h>
#include <stdlib.h>

// TAREA: Declarar funciones de stb_image.c
extern "C" unsigned char* stbi_load(const char* filename, int* x, int* y, int* comp, int req_comp);
extern "C" void stbi_image_free(void* buffer);

Image::Image(const String &filename, uint16 hframes, uint16 vframes) {
	this->filename = filename;
	this->hframes = hframes;
	this->vframes = vframes;
	width = 0;
	height = 0;
	handlex = 0;
	handley = 0;
	gltex = 0;
	lastU = 1.0;
	lastV = 1.0;

	// TAREA: Cargar el buffer de la imagen
	int pwidth;
	int pheight;
	unsigned char* buffer = stbi_load(filename.ToCString(), &pwidth, &pheight, NULL, 4);

	// Generamos la textura
	if ( buffer ) {
		width = (uint16)pwidth;
		height = (uint16)pheight;
		uint16 widthPro = (uint16)pow(2, ceil(Log2(width)));
		uint16 heightPro = (uint16)pow(2, ceil(Log2(height)));
		unsigned char* bufferPro = NULL;
		if (width != widthPro || height != heightPro)
		{
			bufferPro = new unsigned char[widthPro * heightPro * 4];
			memset(bufferPro, 0, widthPro * heightPro * 4);
			for (int i = 0; i < width; i++)
				for (int j = 0; j < height; j++)
					for (int k = 0; k < 4; k++)
						bufferPro[(j*widthPro + i)*4 + k] = buffer[(j*width + i)*4 + k];
			lastU = (double)width / widthPro;
			lastV = (double)height / heightPro;
		}
		glGenTextures(1, &gltex);
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (bufferPro)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthPro, heightPro, 0, GL_RGBA, GL_UNSIGNED_BYTE, bufferPro);
			delete[] bufferPro;
		}
		else
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
		free(buffer);
	}
}

Image::~Image() {
	glDeleteTextures(1, &gltex);
}

void Image::Bind() const {
	// TAREA: Establecer la textura actual
	glBindTexture(GL_TEXTURE_2D, gltex);
}
