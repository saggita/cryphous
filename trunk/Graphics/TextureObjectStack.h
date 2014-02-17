#ifndef __CRYSTAL_GRAPHICS_TEXTURE_OBJECT_STACK_H__
#define __CRYSTAL_GRAPHICS_TEXTURE_OBJECT_STACK_H__

#include <vector>

#include "TextureObject.h"

namespace Crystal {
	namespace Graphics {
		
class TextureObjectStack {
public:
	void push_back(TextureObject* object) {
		textures.push_back( object );
	}

	void apply() {
		for( size_t i = 0; i < textures.size(); ++i ) {
			textures[i]->apply(i);
		}
	}

	void clear() {
		release();
	}

	void release() {
		for( TextureObject* texture : textures ) {
			texture->release();
		}
		textures.clear();
	}

private:
	std::vector<TextureObject*> textures;
};
	}
}

#endif