#ifndef __CAMERA_H__
#define __CAMERA_H__

namespace Crystal{
	namespace Shader{

class Camera{
public:
	static Camera* get() {
		static Camera camera;
		return &camera;
	}

private:
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
};
	}
}
#endif