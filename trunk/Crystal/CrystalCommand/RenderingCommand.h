#pragma once

using namespace System::Drawing;

#include <vector>

namespace Crystal{
	namespace Renderer{
		class PointSpriteFactory;
		struct Point2d;
	}
	namespace Command{
		ref class Command;

public ref class RenderingCommand
{
public:
	RenderingCommand(Command^ mainCommand);

	~RenderingCommand();

	Bitmap^ getSurfaceImage();

	Bitmap^ getThicknessImage();

	Bitmap^ getNormalImage();

	Bitmap^ getDepthImage();

	void setWidth(int width) { this->width = width; }

	void setHeight(int height) { this->height = height; }

private:
	std::vector<Renderer::Point2d> getPointsFromParticles();

private:
	Renderer::PointSpriteFactory* factory;
	Command^ mainCommand;
	int width;
	int height;
};


	}
}