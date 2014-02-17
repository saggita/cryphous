#ifndef __CRYSTAL_GRAPHICS_SHADER_H__
#define __CRYSTAL_GRAPHICS_SHADER_H__

#include <string>

namespace Crystal{
	namespace Graphics {

class Shader
{
public:
	Shader(void);
	
	~Shader(void);

	enum ShaderStage {
		VERTEX_SHADER,
		FRAGMENT_SHADER,
	};

	void compileVertexShader( const std::string& fileName );

	void compileFragmentShader( const std::string& filleName );

	void clear();

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif