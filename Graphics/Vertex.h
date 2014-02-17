#ifndef __CRYSTAL_GRAPHICS_VERTEX_H__
#define __CRYSTAL_GRAPHICS_VERTEX_H__

#include <vector>

namespace Crystal {
	namespace Graphics {

class Vertex {
public:
	Vertex()
	{}

	Vertex( float x, float y, float z ) :
		x( x),
		y( y),
		z( z)
	{
	}

	std::vector<float> toArray() const {
		std::vector<float> result(3);
		result[0] = x;
		result[1] = y;
		result[2] = z;
		return result;
	}

private:
	float x;
	float y;
	float z;
};

class VertexCollection {
public:

	void push_back( const Vertex& vertex ) {
		vertices.push_back( vertex );
	}

	size_t size() const { return vertices.size(); } 

	std::vector<float> toArray() {
		std::vector<float> result;
		for( const Vertex& vertex : vertices ) {
			const std::vector<float> vec = vertex.toArray();
			result.insert( result.end(), vec.begin(), vec.end() );
		}
		return result;
	}

private:
	std::vector<Vertex> vertices;
};
	}
}

#endif