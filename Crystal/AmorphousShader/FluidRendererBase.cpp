#include "StdAfx.h"

#include "FluidRendererBase.h"
#include "FrameBufferObject.h"
#include "VisualParticle.h"

#include <boost/foreach.hpp>

#include <cassert>
#include <cmath>
#include <cstdlib>

using namespace Crystal::Geom;
using namespace Crystal::Shader;

FluidRendererBase::FluidRendererBase(const int width, const int height, const PBFRSetting& setting) :
OnScreenRendererBase( width, height ),
	setting( setting)
{
}

FluidRendererBase::~FluidRendererBase()
{
}

void FluidRendererBase::setBackGround(const Texture& texture)
{
	getOpenGLWrapper()->BeginRendering();
	getOpenGLWrapper()->EndRendering();
}