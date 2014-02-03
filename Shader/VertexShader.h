#ifndef __CRYSTAL_GRAPHICS_VERTEX_SHADER_H__
#define __CRYSTAL_GRAPHICS_VERTEX_SHADER_H__

#include <string>

namespace Crystal{
	namespace Shader{

class VertexShader
{
public:
	VertexShader(void);
	
	~VertexShader(void);

	void createShader(const std::string& fileName);

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif