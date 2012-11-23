#include "StdAfx.h"

#include "FlameRendererBase.h"
#include "FrameBufferObject.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace Amorphous::Geom;
using namespace Amorphous::Color;
using namespace Amorphous::Shader;

FlameRendererBase::FlameRendererBase(const int width, const int height, const PBFRSetting& setting) :
OnScreenRendererBase( width, height ),
backGroundRenderer( width, height, setting.backGroundIntensity ),
	setting( setting)
{
}

FlameRendererBase::~FlameRendererBase()
{
}

void FlameRendererBase::applyBlur()
{
	const float accumRatio = setting.blurRatio;
	glAccum( GL_ACCUM, 1.0f - accumRatio);
	glAccum( GL_RETURN, 1.1f );
	glAccum( GL_LOAD, accumRatio );;
}

void FlameRendererBase::setBackGround(const Texture& texture)
{
	getOpenGLWrapper()->BeginRendering();
	backGroundRenderer.setBackGround(new TextureObject( texture.getPixels(), texture.getWidth(), texture.getHeight() ) );
	getOpenGLWrapper()->EndRendering();
}

void FlameRendererBase::setup(VisualParticleList* visualParticles, std::vector<Amorphous::Shader::PolygonModel>* solidModels) {
	this->visualParticles = visualParticles;
	backGroundRenderer.setSolidModels( solidModels );
}