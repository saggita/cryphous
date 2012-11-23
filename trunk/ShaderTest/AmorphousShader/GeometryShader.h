#ifndef __GEOMETRY_SHADER_H__
#define __GEOMETRY_SHADER_H__

namespace Amorphous{
	namespace Shader{

class GeometryShader
{
public:
	GeometryShader(void);
	~GeometryShader(void);

	void createShader(const char* fullFileName);

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif