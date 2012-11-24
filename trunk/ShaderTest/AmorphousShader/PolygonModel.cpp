#include "StdAfx.h"
#include "PolygonModel.h"

#include <fstream>
#include <iostream>

using namespace Amorphous::Shader;

PolygonModel::PolygonModel(void)
{
}


PolygonModel::~PolygonModel(void)
{
}

void PolygonModel::readFromObjFile(const std::string& fileName)
{
	std::ifstream stream(fileName, std::ios::in);
	std::string lineStr;
	while( !stream.eof() ) {
		std::string head;
		stream >> head;
		if( head == "#") {
			std::string comment;
			std::getline(stream, comment);
		}
		else if( head == "v" ) {
			Vertex vertex;
			stream >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back( vertex );
		}
		else if( head == "f" ) {
			Face face;
			stream >> face.vertex1 >> face.vertex2 >> face.vertex3;
			--face.vertex1; --face.vertex2; --face.vertex3;
			faces.push_back( face );
		}
		else if( head == "vt") {
			TextureCoordinate tc;
			stream >> tc.x >> tc.y;
			textureCoordinates.push_back( tc );
		}
	}
	stream.close();
}

std::vector<double> PolygonModel::getVertices() const
{
	std::vector<double> results;
	std::vector<Face>::const_iterator iter;
	for( iter = faces.begin(); iter != faces.end(); ++iter ) {
		results.push_back( vertices[iter->vertex1].x );
		results.push_back( vertices[iter->vertex1].y );
		results.push_back( vertices[iter->vertex1].z );
		results.push_back( vertices[iter->vertex2].x );
		results.push_back( vertices[iter->vertex2].y );
		results.push_back( vertices[iter->vertex2].z );
		results.push_back( vertices[iter->vertex3].x );
		results.push_back( vertices[iter->vertex3].y );
		results.push_back( vertices[iter->vertex3].z );
	}
	return results;
}

std::vector<double> PolygonModel::getTextureCoordinates() const
{
	std::vector<double> results;
	std::vector<Face>::const_iterator iter;
	for( iter = faces.begin(); iter != faces.end(); ++iter ) {
		results.push_back( textureCoordinates[iter->vertex1].x );
		results.push_back( textureCoordinates[iter->vertex1].y );
		results.push_back( textureCoordinates[iter->vertex2].x );
		results.push_back( textureCoordinates[iter->vertex2].y );
		results.push_back( textureCoordinates[iter->vertex3].x );
		results.push_back( textureCoordinates[iter->vertex3].y );
	}
	return results;
}