#ifndef __CRYSTAL_GRAPHICS_GEOMETRY_SHADER_H__
#define __CRYSTAL_GRAPHICS_GEOMETRY_SHADER_H__

#include <string>

namespace Crystal{
	namespace Shader{

class GeometryShader
{
public:
	GeometryShader(void);

	~GeometryShader(void);

	void createShader(const std::string& fileName);

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif