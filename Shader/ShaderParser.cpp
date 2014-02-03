#include "ShaderParser.h"

#include <vector>
#include <string>
#include <fstream>

using namespace Crystal::Shader;

bool ShaderParser::parse(const std::string& filename)
{
	std::fstream stream( filename);
	
	if( stream.bad() ) {
		return false;
	}

	while( !stream.eof() ) {
		std::string str;
		stream >> str;
		if(str == "in") {
			Input input;
			stream >> input.type;
			stream >> input.name;
			inputs.push_back( input );
		}
		else if( str == "uniform" ) {
			stream >> str;
			uniforms.push_back( str );
		}
	}

	return true;
}