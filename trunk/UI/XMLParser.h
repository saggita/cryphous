#include "tinyxml2.h"

#include "../Math/Vector3d.h"
#include "../Math/Box.h"
#include "../Math/Sphere.h"

#include "../Graphics/Color.h"
#include "../Graphics/RenderingPipeline.h"

#include <vector>


struct PhysicsParam
{
public:
	float getEffectLength() const { return particleDiameter * 1.25f; }

public:
	float pressureCoe;
	float viscosityCoe;
	float timeStep;
	float particleDiameter;
	float density;
	Crystal::Math::Box boundaryBox;
	Crystal::Math::Vector3d externalForce;
	std::vector<Crystal::Math::Box> boxes;
	std::vector<Crystal::Math::Sphere> spheres;
};

class XMLParser {

public:
	static PhysicsParam parsePhysicsParam( const std::string& filename );

	static Crystal::Graphics::RenderingPipeline::Param parseGraphicsParam( const std::string& filename );
};
