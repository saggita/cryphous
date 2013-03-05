#ifndef __CRYPHOUS_VERTEX_SHADER_H__
#define __CRYPHOUS_VERTEX_SHADER_H__

namespace Cryphous{
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