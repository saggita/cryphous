#ifndef __GRAPHICS_SETTINGS_H__
#define __GRAPHICS_SETTINGS_H__

#include "../CrystalUtility/Uncopyable.h"

namespace Crystal{
	namespace Graphics {

class GraphicsSettings : private Uncopyable
{
public:
	int pointSize;
	int pointAlpha;
	float zoom;
	float cameraX;
	float cameraY;
	int angleX;
	int angleY;
	int angleZ;
	bool drawBoundingBox;
	bool doDisplaySurface;

	GraphicsSettings::GraphicsSettings() :
		pointSize( 10 ),
		pointAlpha( 10),
		zoom( 50.0),
		cameraX( 0.0),
		cameraY( 0.0),
		angleX( 0),
		angleY( 0),
		angleZ( 0),
		drawBoundingBox( true),
		doDisplaySurface( false)
		{
		}

	GraphicsSettings::~GraphicsSettings(){}

	void resetCameraAndAngle(){
		cameraX = 0.0f;
		cameraY = 0.0f;
		zoom = 50.0f;
		angleX = 0;
		angleY = 0;
		angleZ = 0;
	}

};

	}
}

#endif