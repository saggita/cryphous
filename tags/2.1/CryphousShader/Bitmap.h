#ifndef __CRYPHOUS_BITMAP_H__
#define __CRYPHOUS_BITMAP_H__

#include <vector>

namespace Cryphous{
	namespace Shader{

class Bitmap
{
public:
	void readFromFile(char *filename);
	Bitmap(char *FileName);

	unsigned long sizeX;
	unsigned long sizeY;
	std::vector<unsigned char> color;
	std::vector<unsigned char> colors;
};
	}
}

#endif