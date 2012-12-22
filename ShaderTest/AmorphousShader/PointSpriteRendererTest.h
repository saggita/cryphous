#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class PointSpriteRenderer;
	}
}

class PointSpriteRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	PointSpriteRendererTest(const int width, const int height);
};