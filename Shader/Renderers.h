#ifndef __CRYSTAL_GRAPHICS_SHADER_RENDERERS_H__
#define __CRYSTAL_GRAPHCIS_SHADER_RENDERERS_H__

#include <map>

#include "VisualParticle.h"

namespace Crystal{
	namespace Shader{
class PointSpriteRenderer;
class DepthRenderer;
class SmoothingRenderer;
class ThicknessRenderer;
class ScreenSpaceFluidRenderer;
class PBVRRenderer;
class OnScreenRenderer;

class TextureObject;


typedef std::map<int, TextureObject*> TextureObjectMap;

class Renderers{
public:
	PointSpriteRenderer* pointSpriteRenderer;
	DepthRenderer* depthRenderer;
	SmoothingRenderer* depthSmoothingRenderer;
	ThicknessRenderer* thicknessRenderer;
	SmoothingRenderer* thicknessSmoothingRenderer;
	ScreenSpaceFluidRenderer* screenSpaceFluidRenderer;
	PBVRRenderer* pbvrRenderer;

	void create();

	void init(const int width, const int height);

	void render();

	void setParticles( const VisualParticleVector& particles);

	TextureObjectMap createTextureObjectMap() const;
	
	OnScreenRenderer* onScreenRenderer;

	TextureObject* selectedTexture;

	~Renderers();

	void setPointSize( const float pointSize ) { m_pointSize = pointSize; }

	float getPointSize() const { return m_pointSize; }

private:
	float m_pointSize;

};

	}
}

#endif