#ifndef __CRYSTAL_GRAPHICS_SHADER_COMMAND_H__
#define __CRYSTAL_GRAPHICS_SHADER_COMMAND_H__

#include <vector>
#include <string>

#include "ShaderObject.h"
#include "GLSLMatrix.h"

namespace Crystal{
	namespace Graphics {

class ShaderCommand{
public:
	virtual ~ShaderCommand(){};

	virtual void enable(ShaderObject* shader) = 0;
};

class UniformIntCommand : public ShaderCommand {
public:
	UniformIntCommand(const std::string& name, const int val) :
		name(name), val(val)
	{}

	void enable(ShaderObject* shader) {
		shader->setUniform(name.c_str(), val);
	}

private:
	std::string name;
	const int val;
};

class UniformCommand : public ShaderCommand {
public:
	UniformCommand(const std::string& name, const float val) :
		name(name), val(val)
	{}

	void enable(ShaderObject* shader) {
		shader->setUniform(name.c_str(), val);
	}

private:
	std::string name;
	const float val;
};

class UniformArrayCommand : public ShaderCommand {
public:
	UniformArrayCommand(const std::string& name, const std::vector< float >& val) :
		name(name), val(val)
	{}

	void enable(ShaderObject* shader) {
		shader->setUniformVector(name.c_str(), &( val.front() ) );
	}

private:
	std::string name;
	const std::vector<float> val;
};

class UniformMatrixCommand : public ShaderCommand {
public:
	UniformMatrixCommand(const std::string& name, const GLSLMatrix& matrix):
		name(name), matrix(matrix)
	{}

	void enable(ShaderObject* shader) {
		shader->setUniformMatrix( name.c_str(), matrix );
	}

private:
	std::string name;
	const GLSLMatrix matrix;
};

class VertexCommand : public ShaderCommand {
public:
	VertexCommand(const std::string& name, const std::vector<float>& values) :
		name( name), values( values)
	{}

	void enable(ShaderObject* shader) {
		shader->setVertex( "position", values );
	}
private:
	std::string name;
	std::vector<float> values;
};

class VertexAttribCommand : public ShaderCommand {
public:
	VertexAttribCommand(const std::string& name, const std::vector<float>& values, int size ) :
		name( name), values( values), size( size)
	{}

	void enable(ShaderObject* shader) {
		shader->setVertexAttrib( name.c_str(), values, size );
	}

private:
	std::string name;
	std::vector<float> values;
	int size;
};

class BindFlagCommand : public ShaderCommand {
public:
	BindFlagCommand(const std::string& name) :
		name(name)
	{}

	void enable(ShaderObject* shader) {
		shader->bindFrag( name.c_str() );
	}

private:
	std::string name;
};

class UniformTextureCommand : public ShaderCommand {
public:
	UniformTextureCommand(const std::string& name, TextureObject* texture) :
		name( name), texture( texture) {
	}

	void enable(ShaderObject* shader) {
		shader->setUniformTexture(name.c_str(), *texture);
	}

private:
	std::string name;
	TextureObject* texture;
};

class DrawPointsCommand : public ShaderCommand {
public:
	DrawPointsCommand(const int size) :
	size( size ) {
	}

	void enable(ShaderObject* shader) {
		shader->drawPoints( size );
	}

private:
	int size;
};

class DrawQuadsCommand : public ShaderCommand {
public:
	DrawQuadsCommand(const int size) :
		size( size ) {
	}

	void enable(ShaderObject* shader) {
		shader->drawQuads( size );
	}

private:
	int size;
};

class ShaderCommandStack {
public:
	~ShaderCommandStack() {
		clear();
	}

	void clear() {
		for( ShaderCommand* command : commands ) {
			delete command;
		}
		commands.clear();
	}

	void push_back(ShaderCommand* command) {
		commands.push_back( command );
	}

	void enable(ShaderObject* shader){
		shader->apply();
		for( ShaderCommand* command : commands ) {
			command->enable(shader);
		}
		shader->release();
	}

private:
	std::vector<ShaderCommand*> commands;
};
	}
}

#endif