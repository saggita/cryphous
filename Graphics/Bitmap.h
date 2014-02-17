#ifndef __CRYSTAL_GRAPHICS_BITMAP_H__
#define __CRYSTAL_GRAPHICS_BITMAP_H__

#include <vector>
#include <string>

namespace Crystal{
	namespace Graphics{

class Bitmap
{
public:
	Bitmap();

	Bitmap(const std::string& filename);

	void readFromFile(const std::string& filename);

	unsigned long getWidth() const { return width; }

	unsigned long getHeight() const { return height; }

	std::vector<unsigned char> getColors() const { return colors; } 

private:
	unsigned long width;
	unsigned long height;
	std::vector<unsigned char> colors;
};
	}
}

#endif