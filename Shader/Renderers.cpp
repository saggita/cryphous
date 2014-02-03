#include "Renderers.h"

#include "PointSpriteRenderer.h"
#include "DepthRenderer.h"
#include "SmoothingRenderer.h"
#include "ThicknessRenderer.h"
#include "ScreenSpaceFluidRenderer.h"
#include "PBVRRenderer.h"
#include "OnScreenRenderer.h"

#include "FrameBufferObject.h"
#include "TextureObject.h"

#include "Bitmap.h"

using namespace Crystal::Shader;

float alpha = 0.2f;

Bitmap bitmap("../Shaders/caustic2.bmp");

void Renderers::create()
{
	pointSpriteRenderer = new PointSpriteRenderer( m_pointSize, alpha);
	depthRenderer = new DepthRenderer( m_pointSize );
	depthSmoothingRenderer = new SmoothingRenderer();
	thicknessRenderer = new ThicknessRenderer( m_pointSize, alpha );
	thicknessSmoothingRenderer = new SmoothingRenderer();
	screenSpaceFluidRenderer = new ScreenSpaceFluidRenderer();
	pbvrRenderer = new PBVRRenderer( m_pointSize, alpha);
	
	onScreenRenderer = new OnScreenRenderer();
}

void Renderers::init(const int width, const int height)
{
	std::vector<ScreenRendererBase*> renders;

	renders.push_back( pointSpriteRenderer );
	renders.push_back( depthRenderer );
	renders.push_back( depthSmoothingRenderer );
	renders.push_back( thicknessRenderer );
	renders.push_back( thicknessSmoothingRenderer );
	renders.push_back( screenSpaceFluidRenderer );
	renders.push_back( pbvrRenderer );
	renders.push_back( onScreenRenderer );

	for( ScreenRendererBase* renderer : renders ) {
		renderer->setWidth( width );
		renderer->setHeight( height );
		renderer->init();
	}

	selectedTexture = &(pointSpriteRenderer->getFrameBufferObject()->getTextureObject());
}

void Renderers::render()
{
	pointSpriteRenderer->render();
	depthRenderer->render();
	depthSmoothingRenderer->setDepthTexture( &(depthRenderer->getFrameBufferObject()->getTextureObject() ) );
	depthSmoothingRenderer->render();
	
	thicknessRenderer->render();
	thicknessSmoothingRenderer->setDepthTexture( &(thicknessRenderer->getFrameBufferObject()->getTextureObject() ) );
	thicknessSmoothingRenderer->render();

	TextureObject bmpTexture( bitmap.getColors(), bitmap.getWidth(), bitmap.getHeight() );

	screenSpaceFluidRenderer->setThicknessTexture( &(thicknessSmoothingRenderer->getFrameBufferObject()->getTextureObject() ) );
	screenSpaceFluidRenderer->setDepthSmoothingTexture( &(depthSmoothingRenderer->getFrameBufferObject()->getTextureObject() ) );
	screenSpaceFluidRenderer->setBackgroundTexture( &bmpTexture );
	screenSpaceFluidRenderer->render();

	pbvrRenderer->render();

	onScreenRenderer->setTexture( selectedTexture );
	onScreenRenderer->render();
}

TextureObjectMap Renderers::createTextureObjectMap() const
{
	TextureObjectMap map;
	map[0] = &(pointSpriteRenderer->getFrameBufferObject()->getTextureObject() );
	map[1] = &(depthRenderer->getFrameBufferObject()->getTextureObject() );
	map[2] = &(depthSmoothingRenderer->getFrameBufferObject()->getTextureObject() );
	map[3] = &(thicknessSmoothingRenderer->getFrameBufferObject()->getTextureObject() );
	map[4] = &(screenSpaceFluidRenderer->getFrameBufferObject()->getTextureObject() );
	map[5] = &(pbvrRenderer->getFrameBufferObject()->getTextureObject() );

	return map;
}

#include "VisualParticleConverter.h"

void Renderers::setParticles(const VisualParticleVector& particles)
{
	std::vector<float> positions = VisualParticleConverter::toPositionArray( particles );
	std::vector<float> densities = VisualParticleConverter::toDensityArray( particles );
	std::vector<float> colors = VisualParticleConverter::toColorArray( particles );

	depthRenderer->setVisualParticles( positions, densities );
	thicknessRenderer->setVisualParticles( positions, densities );
	pointSpriteRenderer->setVisualParticles( positions, colors );
	pbvrRenderer->setVisualParticles( positions, colors );
}

Renderers::~Renderers()
{
	delete pointSpriteRenderer;
	delete depthRenderer;
	delete screenSpaceFluidRenderer;
	delete onScreenRenderer;
}