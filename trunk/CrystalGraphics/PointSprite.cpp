#include <Windows.h>
#include "GLee.h"

#include "PointSprite.h"

#include "TextureCreator.h"

#include "GraphicsSettings.h"

using namespace Crystal::Graphics;

PointSprite::PointSprite(void)
{
	const int size = 16;

	TextureCreator textureCreator;
	textureCreator.createTexture( size );
	GLubyte *bytes = textureCreator.getTexture();

	glTexEnvi( GL_POINT_SPRITE, GL_COORD_REPLACE, GL_MODULATE );

	glPixelStorei( GL_UNPACK_ALIGNMENT, 1 );

	glTexImage2D( GL_TEXTURE_2D, 0, GL_ALPHA, size, size, 0, GL_ALPHA,
		GL_UNSIGNED_BYTE, bytes );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
}

PointSprite::~PointSprite(void)
{
}

void PointSprite::apply()
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_POINT_SPRITE);
}

void PointSprite::release()
{
	glDisable(GL_POINT_SPRITE);
	glDisable(GL_TEXTURE_2D );
}