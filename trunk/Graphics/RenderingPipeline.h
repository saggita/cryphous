#ifndef __CRYSTAL_GRAPHICS_RENDERING_PIPELINE_H__
#define __CRYSTAL_GRAPHICS_RENDERING_PIPELINE_H__

#include <map>
#include <vector>
#include <memory>

#include "ShaderObject.h"

#include "TextureObject.h"
#include "FrameBufferObject.h"

#include "RenderingCommand.h"
#include "ShaderCommand.h"
#include "TextureObjectStack.h"

#include "RenderingUnit.h"

#include "Bitmap.h"
#include "Vertex.h"

namespace Crystal {
	namespace Graphics {

		class Camera;

typedef std::map<int, TextureObject*> TextureObjectMap;

class RenderingPipeline {
private:
	RenderingUnit pointSprite;
	RenderingUnit depth;
	RenderingUnit depthSmoothing;
	RenderingUnit thickness;
	RenderingUnit thicknessSmoothing;
	RenderingUnit fluid;
	RenderingUnit normal;
	RenderingUnit scene;

	ShaderObject onScreenShader;

	TextureObject backgroundTexture;

public:
	struct Param {
		float pointSize;
		float alpha;
		int filterRadius;
		Color fluidColor;
		Color diffuseColor;
		Color specularColor;
		Vertex lightPosition;
	};

public:
	void build(const int width, const int height);

	void render( const int width, const int height, const std::vector< float >& positions, const std::vector< float >& colors, Camera* camera, const Param& param );
	
	TextureObject* selectedTexture;

	TextureObject* getPointSpriteTexture() const {
		return pointSprite.getTexture();
	}

	TextureObject* getDepthTexture() const {
		return depth.getTexture();
	}

	TextureObject* getDepthSmoothingTexture() const {
		return depthSmoothing.getTexture();
	}

	TextureObject* getThicknessTexture() const {
		return thickness.getTexture();
	}

	TextureObject* getThicknessSmoothingTexture() const {
		return thicknessSmoothing.getTexture();
	}

	TextureObject* getNormalTexture() const {
		return normal.getTexture();
	}

	TextureObject* getFluidTexture() const {
		return fluid.getTexture();
	}

	TextureObject* getSceneTexture() const {
		return scene.getTexture();
	}

private:
	Bitmap bitmap;
};

	}
}

#endif