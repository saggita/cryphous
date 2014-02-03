#ifndef __CRYSTAL_GRAPHICS_FRAGMENT_SHADER_H__
#define __CRYSTAL_GRAPHICS_FRAGMENT_SHADER_H__

#include <string>

namespace Crystal{
	namespace Shader{

class FragmentShader
{
public:
	FragmentShader(void);

	~FragmentShader(void);

	void createShader(const std::string& fileName);

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif