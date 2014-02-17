#ifndef __CRYSTAL_GRAPHICS_SHADER_PARSER_H__
#define __CRYSTAL_GRAPHCIS_SHADER_PARSER_H__

#include <string>
#include <vector>

namespace Crystal{
	namespace Shader{

class ShaderParser {
public:
	bool parse(const std::string& filename);

	class Input{
	public:
		std::string type;
		std::string name;
	};

	std::vector<Input> getInputs() const { return inputs; }

private:
	std::vector< Input > inputs;
	std::vector< std::string > uniforms;
};
	}
}

#endif