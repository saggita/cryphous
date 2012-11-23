#ifndef __VERTEX_SHADER_H__
#define __VERTEX_SHADER_H__

namespace Amorphous{
	namespace Shader{

class VertexShader
{
public:
	VertexShader(void);
	
	~VertexShader(void);

	void createShader(const char* fullFileName);

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif