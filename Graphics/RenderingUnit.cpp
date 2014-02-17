#include "RenderingUnit.h"

using namespace Crystal::Graphics;

#include <cassert>

void RenderingUnit::build( const std::string& shaderName, const int width, const int height ) {
	clear();
	shader.build( shaderName );
	fbo.reset( new FrameBufferObject( width, height ) );
}

void RenderingUnit::render( const int width, const int height )
{
	assert( GL_NO_ERROR == glGetError() );

	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, fbo->getID() );
	glViewport( 0, 0, width, height );

	commands.enable();

	textures.apply();

	sCommands.enable( &shader );

	textures.release();

	commands.disable();

	glBindFramebufferEXT( GL_FRAMEBUFFER_EXT, 0 );

	assert( GL_NO_ERROR == glGetError() );
}
