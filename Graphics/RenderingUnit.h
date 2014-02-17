#ifndef __CRYSTAL_GRAPHICS_RENDERING_UNIT_H__
#define __CRYSTAL_GRAPHICS_RENDERING_UNIT_H__

#include "TextureObject.h"
#include "FrameBufferObject.h"
#include "ShaderObject.h"
#include "TextureObjectStack.h"
#include "RenderingCommand.h"
#include "ShaderCommand.h"

#include <memory>

namespace Crystal {
	namespace Graphics {

struct RenderingUnit {
	TextureObject* getTexture() const { return fbo->getTextureObject(); }

	ShaderObject* getShader() { return &shader; }

	FrameBufferObject* getFBO() { return fbo.get(); }
		
	void build( const std::string& shaderName, const int width, const int height );

	void render( const int width, const int height );

	void pushCommand( RenderingCommand* command ) { commands.push_back( command ); }

	void clearTextures() { textures.clear(); }

	void pushTexture( TextureObject* texture ) { textures.push_back( texture ); }

	void clearShaders() { sCommands.clear(); }

	void pushShader( ShaderCommand* command ) { sCommands.push_back( command ); }

	void clear() {
		clearTextures();
		clearShaders();
		sCommands.clear();
		fbo.release();
	}

private:
	TextureObjectStack textures;
	RenderingCommandStack commands;
	ShaderCommandStack sCommands;
	ShaderObject shader;
	std::unique_ptr< FrameBufferObject > fbo;
};

	}
}

#endif