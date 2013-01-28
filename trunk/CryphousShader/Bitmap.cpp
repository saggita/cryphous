#include "Bitmap.h"
#include <cstdio>
#include <cstdlib>
#include <cassert>

using namespace Cryphous::Shader;

Bitmap::Bitmap(char *FileName){
	readFromFile(FileName);
}

void Bitmap::readFromFile(char *FileName) {
	FILE *File = fopen(FileName, "rb");

	fseek(File, 18, SEEK_CUR);

	fread(&sizeX, 4, 1, File);
	fread(&sizeY, 4, 1, File);

	int size = sizeX * sizeY * 3;

	unsigned short int planes;
	fread(&planes, 2, 1, File);
	assert( planes == 1 );

	unsigned short int bpp;
	fread(&bpp, 2, 1, File);
	assert (bpp == 24);

	fseek(File, 24, SEEK_CUR);
	color.resize(size);
	
	fread(&(color.front()), size, 1, File);
	
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
