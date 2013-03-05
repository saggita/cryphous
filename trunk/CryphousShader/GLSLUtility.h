#ifndef __CRYPHOUS_GLSL_UTILITY_H__
#define __CRYPHOUS_GLSL_UTILITY_H__

#include <string>
#include <vector>

namespace Cryphous{
	namespace Shader{

class GLSLUtility
{
public:
	GLSLUtility(void);
	
	~GLSLUtility(void);

	static const std::string LoadShaderText(const char *fileName);

	static void checkError();

	static bool hasNoError();

	static bool hasNoShaderError(const unsigned int shader);
};

	}
}

#endif