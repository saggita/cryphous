#ifndef __CRYSTAL_GRAPHICS_BITMAP_H__
#define __CRYSTAL_GRAPHICS_BITMAP_H__

#include <vector>
#include <string>

namespace Crystal{
	namespace Shader{

class Bitmap
{
public:
	Bitmap();

	Bitmap(const std::string& filename);

	void readFromFile(const std::string& filename);

	unsigned long getWidth() const { return sizeX; }

	unsigned long getHeight() const { return sizeY; }

	std::vector<unsigned char> getColors() const { return colors; } 

private:
	unsigned long sizeX;
	unsigned long sizeY;
	std::vector<unsigned char> color;
	std::vector<unsigned char> colors;
};
	}
}

#endif