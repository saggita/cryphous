#ifndef __POLYGON_MODEL_H__
#define __POLYGON_MODEL_H__

#include <vector>
#include <string>

namespace Amorphous{
	namespace Geom{
		class Point3d;
	}
	namespace Shader{

struct Vertex{
	Vertex(){};
	Vertex(const float x, const float y, const float z) :
	x(x), y(y), z(z)
	{
	}
	float x;
	float y;
	float z;
};

struct TextureCoordinate{
	TextureCoordinate(){};
	TextureCoordinate(const float x, const float y) :
	x(x), y(y)
	{
	}
	float x;
	float y;
};

struct Face{
	Face(){};
	Face(const int vertex1, const int vertex2, const int vertex3) :
	vertex1( vertex1), vertex2( vertex2), vertex3( vertex3)
	{
	}
	int vertex1;
	int vertex2;
	int vertex3;
};

class PolygonModel
{
public:
	PolygonModel(void);

	~PolygonModel(void);

	void readFromObjFile(const std::string& fileName);

	void set(const std::vector<Vertex>& vertices, const std::vector<Face>& faces, const std::vector<TextureCoordinate>& texCoords){ this->vertices = vertices; this->faces = faces; this->textureCoordinates = texCoords; }

	std::vector<double> getVertices() const;

	//std::vector<double> getNormals() const;

	std::vector<double> getTextureCoordinates() const;

	size_t getVerticesSize() const { return vertices.size(); }

	size_t getFacesSize() const { return faces.size(); }

private:
	std::vector<Vertex> vertices;
	std::vector<Face> faces;
	//std::vector<Vertex> normals;
	std::vector<TextureCoordinate> textureCoordinates;
};

	}
}

#endif