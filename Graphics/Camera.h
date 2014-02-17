#ifndef __CRYSTAL_GRAPHICS_CAMERA_H__
#define __CRYSTAL_GRAPHCIS_CAMERA_H__

#include "GLSLMatrix.h"

namespace Crystal {
	namespace Graphics {

class Camera{
public:
	Camera()
	{
		init();
	}

public:
	void init(){
		cameraX = 0.0f;
		cameraY = 0.0f;
		zoom = -0.5f;
		angleX = 0.0f;
		angleY = 0.0f;
		angleZ = 0.0f;
	}

	float zoom;
	float cameraX;
	float cameraY;
	float angleX;
	float angleY;
	float angleZ;

	GLSLMatrix getModelviewMatrix() {
		GLSLMatrix modelviewMatrix;
		modelviewMatrix.translate( cameraX, cameraY, zoom );
		modelviewMatrix.rotateX( angleX );
		modelviewMatrix.rotateY( angleY );
		modelviewMatrix.rotateZ( angleZ );
		return modelviewMatrix;
	}

};
	}
}
#endif