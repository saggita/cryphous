#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <vector>
#include <cassert>

namespace Amorphous{
	namespace Color{

typedef std::vector< unsigned char > Pixels;

class Texture
{
public:
	Texture(void):
	width(0),
	height(0)
	{};

	Texture( const Pixels& pixels, const int width, const int height ) :
	pixels( pixels),
	width( width),
	height( height){
		assert( width * height * 4 == pixels.size() );
	}

	~Texture(void);

	Pixels getPixels() const { return pixels; }

	int getWidth() const { return width; }

	int getHeight() const { return height; }

	bool equals(const Texture& rhs){
		if(width != rhs.getWidth() ||
			height != rhs.getHeight() ||
			pixels.size() != rhs.getPixels().size() ){
				return false;
		}

		for( size_t i = 0; i < pixels.size(); ++i ) {
			if( pixels[i] != rhs.getPixels()[i] ) {
				return false;
			}
		}
		return true;
	}

	bool operator==(const Texture& rhs){
		return equals(rhs);
	}

	bool operator!=(const Texture& rhs){
		return !equals(rhs);
	}

private:
	Pixels pixels;
	int width;
	int height;
};

	}
}
#endif __TEXTURE_H__