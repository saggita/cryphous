#pragma once

#include <memory>

namespace Amorphous{
	namespace Shader{
		class DepthRenderer;
	}
}

class DepthRendererTest : public Amorphous::Shader::OnScreenRendererBase
{
public:
	DepthRendererTest(const int width, const int height);
};