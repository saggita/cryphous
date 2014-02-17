#include "XMLParser.h"

#include "../Graphics/Color.h"

using namespace tinyxml2;

using namespace Crystal::Math;
using namespace Crystal::Graphics;

Vector3d parse( XMLElement* element )
{
	float x, y, z;
	element->QueryFloatAttribute( "x", &x );
	element->QueryFloatAttribute( "y", &y );
	element->QueryFloatAttribute( "z", &z );
	return Vector3d( x, y, z );
}

Vertex parseVertex( XMLElement* element )
{
	float x, y, z;
	element->QueryFloatAttribute( "x", &x );
	element->QueryFloatAttribute( "y", &y );
	element->QueryFloatAttribute( "z", &z );
	return Vertex( x, y, z );
}

float parseFloat( XMLElement* element )
{
	float value;
	element->QueryFloatAttribute( "v", &value );
	return value;	
}

Color parseColor( XMLElement* element )
{
	float red;
	element->QueryFloatAttribute( "r", &red );
	float green;
	element->QueryFloatAttribute( "g", &green );
	float blue;
	element->QueryFloatAttribute( "b", &blue );
	return Color( red, green, blue, 1.0 );
}

PhysicsParam XMLParser::parsePhysicsParam( const std::string& filename )
{
	PhysicsParam param;

	XMLDocument doc;
	doc.LoadFile( filename.c_str() );

	XMLElement* root = doc.FirstChildElement( "physics" );

	XMLElement* minElem = root->FirstChildElement("boundaryMin");
	Vector3d boundaryMin = ::parse( minElem );
	XMLElement* maxElem = root->FirstChildElement("boundaryMax");
	Vector3d boundaryMax = ::parse( maxElem );
	param.boundaryBox = Box( boundaryMin, boundaryMax );

	XMLElement* minObjElem = root->FirstChildElement( "objectMin" );
	XMLElement* maxObjElem = root->FirstChildElement( "objectMax" );

	while( minObjElem != NULL  && maxObjElem != NULL ) {
		Vector3d min = ::parse( minObjElem );
		Vector3d max = ::parse( maxObjElem );
		param.boxes.push_back( Box( min, max ) );
		minObjElem = minObjElem->NextSiblingElement( "objectMin" );
		maxObjElem = maxObjElem->NextSiblingElement( "objectMax" );
	}

	XMLElement* centerElem = root->FirstChildElement( "sphereCenter" );
	XMLElement* radiusElem = root->FirstChildElement( "sphereRadius" );

	while( centerElem != NULL && radiusElem != NULL ) {
		const Vector3d center = ::parse( centerElem );
		const float radius = ::parseFloat( radiusElem );
		param.spheres.push_back( Sphere( center, radius )  );
		
		centerElem = centerElem->NextSiblingElement( "sphereCenter" );
		radiusElem = radiusElem->NextSiblingElement( "sphereRadius");
	}

	param.externalForce = ::parse( root->FirstChildElement("externalForce") );
	
	XMLElement* diameterElem = root->FirstChildElement("particleDiameter");
	param.particleDiameter = ::parseFloat( diameterElem );
	XMLElement* timeStepElem = root->FirstChildElement("timeStep");
	param.timeStep = ::parseFloat( timeStepElem );
	XMLElement* pressureCoeElem = root->FirstChildElement("pressureCoe");
	param.pressureCoe = ::parseFloat( pressureCoeElem );
	XMLElement* viscCoeElem = root->FirstChildElement("viscosityCoe");
	param.viscosityCoe = ::parseFloat( viscCoeElem );;

	XMLElement* densityElem = root->FirstChildElement( "density" );
	param.density = ::parseFloat( densityElem );

	return param;
}

RenderingPipeline::Param XMLParser::parseGraphicsParam( const std::string& filename )
{
	RenderingPipeline::Param param;

	XMLDocument doc;
	doc.LoadFile( filename.c_str() );

	XMLElement* root = doc.FirstChildElement( "color" );

	XMLElement* fluid = root->FirstChildElement( "fluid" );
	param.fluidColor = parseColor( fluid );

	XMLElement* diffuse = root->FirstChildElement( "diffuse" );
	param.diffuseColor = parseColor( diffuse );

	XMLElement* specular = root->FirstChildElement( "specular" );
	param.specularColor = parseColor( specular );

	XMLElement* pointSizeElem = root->FirstChildElement( "pointSize" );
	pointSizeElem->QueryFloatAttribute( "v", &param.pointSize );

	XMLElement* alphaElem = root->FirstChildElement( "alpha" );
	alphaElem->QueryFloatAttribute( "v", &param.alpha );

	XMLElement* filterRadiusElem = root->FirstChildElement( "filterRadius" );
	filterRadiusElem->QueryIntAttribute( "v", &param.filterRadius );

	XMLElement* lightPositionElem = root->FirstChildElement( "lightPosition" );
	param.lightPosition = ::parseVertex( lightPositionElem );

	return param;
}