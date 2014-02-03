#ifndef __CRYSTAL_GRAPHICS_RENDERING_COMMAND_H__
#define __CRYSTAL_GRAPHICS_RENDERING_COMMAND_H__

#include <vector>

#include "Color.h"

namespace Crystal{
	namespace Shader{

class RenderingCommand
{
public:
	virtual void enable() = 0;

	virtual void disable() = 0;

	virtual ~RenderingCommand(){};
};

class PointSpriteCommand : public RenderingCommand
{
public:
	virtual void enable();

	virtual void disable();
};

class DepthTestCommand : public RenderingCommand
{
public:
	virtual void enable();

	virtual void disable();
};

class ColorBufferClearCommand : public RenderingCommand
{
public:
	ColorBufferClearCommand(const Color& color) :
		color( color )
	{
	}
	virtual void enable();

	virtual void disable();

private:
	const Color color;
};

class DepthBufferClearCommand : public RenderingCommand
{
public:
	virtual void enable();

	virtual void disable();
};

class BlendingCommand : public RenderingCommand
{
public:
	virtual void enable();

	virtual void disable();
};

class RenderingCommandStack
{
public:
	~RenderingCommandStack();

	void push_back(RenderingCommand* command);

	void enable();

	void disable();

private:
	std::vector<RenderingCommand*> commands;
};
	}
}

#endif