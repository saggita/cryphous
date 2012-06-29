#include "ApplicationSettings.h"

#include "XMLWriter.h"
#include "XMLReader.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"
#include "../CrystalPhysics/Simulation.h"
#include "../CrystalGraphics/Renderer.h"

#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System::Xml;

ApplicationSettings::ApplicationSettings(void)
{
	factory = new PhysicsObjectFactory;
	simulation = new Simulation;
	simulationSetting = new SimulationSetting;
	renderer = new Renderer;
	conditions = new std::list<PhysicsObjectCondition>;
}

ApplicationSettings::~ApplicationSettings()
{
	delete conditions;
	delete renderer;
	delete simulationSetting;
	delete simulation;
	delete factory;
}

void ApplicationSettings::refresh()
{
	factory->init();
	BOOST_FOREACH(const PhysicsObjectCondition& condition, *conditions ) {
		factory->createPhysicsObject(condition, *simulationSetting);
	}
	renderer->init();	
	simulation->init();
}

XmlDocument^ ApplicationSettings::writeToXML()
{
	XmlDocument^ doc = gcnew XmlDocument();
	doc->AppendChild( doc->CreateXmlDeclaration("1.0", "UTF-8", nullptr ) );

	XmlElement^ root = doc->CreateElement("PhysicsObjects");
	doc->AppendChild( root );

	XmlElement^ commonElement = doc->CreateElement("common");
	root->AppendChild( commonElement );
	{
		XmlElement^ timeStepElement = doc->CreateElement("timeStep");
		timeStepElement->AppendChild( doc->CreateTextNode( simulationSetting->timeStep.ToString() ) );
		commonElement->AppendChild( timeStepElement );

		XmlElement^ effectLengthElement = doc->CreateElement("particleDiameter");
		effectLengthElement->AppendChild( doc->CreateTextNode( simulationSetting->particleDiameter.ToString() ) );
		commonElement->AppendChild( effectLengthElement );
	}

	XmlElement^ boundaryElement = doc->CreateElement("boundary");
	root->AppendChild( boundaryElement );
	{
		XMLWriter writer( doc );
		XmlElement^ boxElement = writer.write( simulationSetting->boundaryBox );
		boundaryElement->AppendChild( boxElement );
	}

	XmlElement^ objectsElement = doc->CreateElement("objects");
	root->AppendChild( objectsElement );

	BOOST_FOREACH( const PhysicsObjectCondition& condition, *conditions ) {
		XmlElement^ objectElement = doc->CreateElement("object");
		objectsElement->AppendChild( objectElement );

		{
			XmlElement^ typeElement = doc->CreateElement("type");
			typeElement->AppendChild( doc->CreateTextNode( ((int)(condition.getObjectType())).ToString() ) );
			objectElement->AppendChild( typeElement );

			XmlElement^ densityElement = doc->CreateElement("density");
			densityElement->AppendChild( doc->CreateTextNode( condition.getDensity().ToString() ) );
			objectElement->AppendChild( densityElement );

			XmlElement^ pressureCoefficientElement = doc->CreateElement("pressureCoefficient");
			pressureCoefficientElement->AppendChild( doc->CreateTextNode( condition.getPressureCoefficient().ToString() ) );
			objectElement->AppendChild( pressureCoefficientElement );

			XmlElement^ viscosityCoefficientElement = doc->CreateElement("viscosityCoefficient");
			viscosityCoefficientElement->AppendChild( doc->CreateTextNode( condition.getViscosityCoefficient().ToString() ) );
			objectElement->AppendChild( viscosityCoefficientElement );
		}
	}

	return doc;
}

bool ApplicationSettings::readFromXML( XmlDocument^ doc )
{
	conditions->clear();
	factory->init();
	SimulationSetting* simulationSetting = ApplicationSettings::get()->simulationSetting;

	XmlElement^ root = doc->DocumentElement;

	XmlElement^ commonElement = (XmlElement^)root->FirstChild;
		XmlElement^ timeStepElement = (XmlElement^)commonElement->FirstChild;
		XmlElement^ effectLengthElement = (XmlElement^)timeStepElement->NextSibling;

		simulationSetting->timeStep = double::Parse( timeStepElement->FirstChild->Value );
		simulationSetting->particleDiameter = double::Parse( effectLengthElement->FirstChild->Value );

	XMLReader reader;
	XmlElement^ boundaryElement = (XmlElement^)commonElement->NextSibling;
	{
		XmlElement^ boxElement = (XmlElement^)boundaryElement->FirstChild;
		const Box& boundaryBox = reader.readBox( boxElement );
		simulationSetting->boundaryBox = boundaryBox;
	}

	XmlElement^ objectElement = (XmlElement^)boundaryElement->NextSibling;
	for each( XmlElement^ element in objectElement->ChildNodes ) {
		XmlElement^ typeElement = (XmlElement^)element->FirstChild;
		XmlElement^ densityElement = (XmlElement^)typeElement->NextSibling;
		XmlElement^ pressureElement = (XmlElement^)densityElement->NextSibling;
		XmlElement^ viscosityElement = (XmlElement^)pressureElement->NextSibling;
		XmlElement^ divideElement = (XmlElement^)viscosityElement->NextSibling;

		const int type = int::Parse( typeElement->FirstChild->Value );
		const double density = double::Parse( densityElement->FirstChild->Value );
		const double pressure = double::Parse( pressureElement->FirstChild->Value );
		const double viscosity = double::Parse( viscosityElement->FirstChild->Value );

		std::vector<Vector3d> points;
		PhysicsObjectCondition* condition = 
			new PhysicsObjectCondition( points, density, pressure, viscosity, (PhysicsObjectCondition::ObjectType)type );

		factory->createPhysicsObject( *condition, *simulationSetting );
		conditions->push_back(*condition);
	}
	return true;
}