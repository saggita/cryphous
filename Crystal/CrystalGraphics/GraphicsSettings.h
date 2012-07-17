#pragma once

#include <boost/noncopyable.hpp>

namespace Crystal{
	namespace Graphics {

class GraphicsSettings : private boost::noncopyable
{
public:
	bool bPointSprite;
	int pointSize;
	int pointAlpha;
	float zoom;
	float cameraX;
	float cameraY;
	int angleX;
	int angleY;
	int angleZ;
	bool drawBoundingBox;

	static GraphicsSettings* get() {
		static GraphicsSettings settings;
		return &settings;
	}

	void resetCameraAndAngle(){
		cameraX = 0.0f;
		cameraY = 0.0f;
		zoom = 50.0f;
		angleX = 0;
		angleY = 0;
		angleZ = 0;
	}

private:
	GraphicsSettings::GraphicsSettings() :
		pointSize( 10 ),
		pointAlpha( 10),
		bPointSprite( true),
		zoom( 50.0),
		cameraX( 0.0),
		cameraY( 0.0),
		angleX( 0),
		angleY( 0),
		angleZ( 0),
		drawBoundingBox( true)
		{
		}

	GraphicsSettings::~GraphicsSettings(){}
};

	}
}