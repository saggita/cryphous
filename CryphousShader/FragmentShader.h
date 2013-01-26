#ifndef __FRAGMENT_SHADER_H__
#define __FRAGMENT_SHADER_H__

namespace Cryphous{
	namespace Shader{

class FragmentShader
{
public:
	FragmentShader(void);

	~FragmentShader(void);

	void createShader(const char* fullFileName);

	unsigned int getID() const { return id; }

private:
	unsigned int id;
};

	}
}

#endif