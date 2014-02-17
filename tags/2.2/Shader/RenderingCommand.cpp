#include "GLee.h"

#include "RenderingCommand.h"

#include "Color.h"

using namespace Crystal::Shader;

void PointSpriteCommand::enable()
{
	glEnable(GL_POINT_SPRITE);
	glEnable(GL_VERTEX_PROGRAM_POINT_SIZE); 
}

void PointSpriteCommand::disable()
{
	glDisable(GL_VERTEX_PROGRAM_POINT_SIZE);
	glDisable(GL_POINT_SPRITE);
}

void DepthTestCommand::enable()
{
	glEnable(GL_DEPTH_TEST);
}

void DepthTestCommand::disable()
{
	glDisable(GL_DEPTH_TEST);
}

void ColorBufferClearCommand::enable()
{
	glClearColor( color.red, color.green, color.blue, color.alpha );
	glClear( GL_COLOR_BUFFER_BIT );
}

void ColorBufferClearCommand::disable()
{
}

void DepthBufferClearCommand::enable()
{
	glClear( GL_DEPTH_BUFFER_BIT );
}

void DepthBufferClearCommand::disable()
{
}

void BlendingCommand::enable()
{
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
}

void BlendingCommand::disable()
{
	glDisable( GL_BLEND );
	glEnable( GL_DEPTH_TEST );
}

RenderingCommandStack::~RenderingCommandStack()
{
	for( RenderingCommand* command : commands ) {
		delete command;
	}
}

void RenderingCommandStack::push_back(RenderingCommand* command)
{
	commands.push_back( command );
}

void RenderingCommandStack::enable()
{
	for( RenderingCommand* command : commands ) {
		command->enable();
	}
}

void RenderingCommandStack::disable()
{
	for( std::vector<RenderingCommand*>::reverse_iterator iter = commands.rbegin(); iter != commands.rend(); ++iter ) {
		(*iter)->disable();
	}
}