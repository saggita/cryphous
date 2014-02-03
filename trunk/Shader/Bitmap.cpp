#define _CRT_SECURE_NO_WARNINGS

#include "Bitmap.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace Crystal::Shader;

Bitmap::Bitmap()
{
}

Bitmap::Bitmap(const std::string& filename)
{
	readFromFile(filename);
}

void Bitmap::readFromFile(const std::string& filename)
{
	FILE *file = fopen(filename.c_str(), "rb");

	fseek(file, 18, SEEK_CUR);

	fread(&sizeX, 4, 1, file);
	fread(&sizeY, 4, 1, file);

	int size = sizeX * sizeY * 3;

	unsigned short int planes;
	fread(&planes, 2, 1, file);
	assert( planes == 1 );

	unsigned short int bpp;
	fread(&bpp, 2, 1, file);
	assert (bpp == 24);

	fseek(file, 24, SEEK_CUR);
	color.resize(size);
	
	fread(&(color.front()), size, 1, file);
	
	for (int i=0;i<size;i+=3) { //bgr -> rgba
		unsigned char temp = color[i];
		color[i] = color[i+2];
		color[i+2] = temp;
	}

	colors.resize( sizeX * sizeY * 4);
	int index = 0;
	for( int i = 0; i < size; i+=3 ) {
		colors[index++] = color[i];
		colors[index++] = color[i+1];
		colors[index++] = color[i+2];
		colors[index++] = 255;
	}
};
