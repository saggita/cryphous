#include "ApplicationSettings.h"

#include "XMLWriter.h"
#include "XMLReader.h"

#include "../CrystalGeom/Point3d.h"
#include "../CrystalGeom/Box.h"
#include "../CrystalPhysics/PhysicsObjectCondition.h"
#include "../CrystalGraphics/GraphicsSettings.h"
#include "../CrystalPhysics/PhysicsObjectFactory.h"
#include "../CrystalPhysics/SimulationSetting.h"


#include <boost/foreach.hpp>

using namespace Crystal::Geom;
using namespace Crystal::Physics;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System::Xml;

ApplicationSettings::ApplicationSettings(void)
{
	factory = new PhysicsObjectFactory;
}

ApplicationSettings::~ApplicationSettings()
{
	delete factory;
}

XmlDocument^ ApplicationSettings::writeToXML()
{
	const PhysicsObjectConditionList& conditions = factory->getConditions();

	SimulationSetting* simulationSetting = SimulationSetting::get();

	XmlDocument^ doc = gcnew XmlDocument();
	doc->AppendChild( doc->CreateXmlDeclaration("1.0", "UTF-8", nullptr ) );

	XmlElement^ root = doc->CreateElement("PhysicsObjects");
	doc->AppendChild( root );

	// 共通条件を書き出す.
	XmlElement^ commonElement = doc->CreateElement("common");
	root->AppendChild( commonElement );
	{
		XmlElement^ timeStepElement = doc->CreateElement("timeStep");
		timeStepElement->AppendChild( doc->CreateTextNode( simulationSetting->timeStep.ToString() ) );
		commonElement->AppendChild( timeStepElement );

		XmlElement^ effectLengthElement = doc->CreateElement("effectLength");
		effectLengthElement->AppendChild( doc->CreateTextNode( simulationSetting->effectLength.ToString() ) );
		commonElement->AppendChild( effectLengthElement );
	}

	// 境界条件を書き出す.
	XmlElement^ boundaryElement = doc->CreateElement("boundary");
	root->AppendChild( boundaryElement );
	{
		XMLWriter writer( doc );
		XmlElement^ boxElement = writer.write( simulationSetting->boundaryBox );
		boundaryElement->AppendChild( boxElement );
	}

	// 物理オブジェクト生成条件を書き出す.
	XmlElement^ objectsElement = doc->CreateElement("objects");
	root->AppendChild( objectsElement );

	BOOST_FOREACH( const PhysicsObjectCondition* condition, conditions ) {
		XmlElement^ objectElement = doc->CreateElement("object");
		objectsElement->AppendChild( objectElement );

		{
			XmlElement^ typeElement = doc->CreateElement("type");
			typeElement->AppendChild( doc->CreateTextNode( ((int)(condition->getObjectType())).ToString() ) );
			objectElement->AppendChild( typeElement );

			XMLWriter writer( doc );
			XmlElement^ boxElement = writer.write( condition->getBox() );
			objectElement->AppendChild( boxElement );

			XmlElement^ densityElement = doc->CreateElement("density");
			densityElement->AppendChild( doc->CreateTextNode( condition->getDensity().ToString() ) );
			objectElement->AppendChild( densityElement );

			XmlElement^ pressureCoefficientElement = doc->CreateElement("pressureCoefficient");
			pressureCoefficientElement->AppendChild( doc->CreateTextNode( condition->getPressureCoefficient().ToString() ) );
			objectElement->AppendChild( pressureCoefficientElement );

			XmlElement^ viscosityCoefficientElement = doc->CreateElement("viscosityCoefficient");
			viscosityCoefficientElement->AppendChild( doc->CreateTextNode( condition->getViscosityCoefficient().ToString() ) );
			objectElement->AppendChild( viscosityCoefficientElement );

			XmlElement^ divideLengthElement = doc->CreateElement("divideLength");
			divideLengthElement->AppendChild( doc->CreateTextNode( condition->getDivideLength().ToString() ) );
			objectElement->AppendChild( divideLengthElement );
		}
	}

	return doc;
}

bool ApplicationSettings::readFromXML( XmlDocument^ doc )
{
	factory->init();
	SimulationSetting* simulationSetting = SimulationSetting::get();

	XmlElement^ root = doc->DocumentElement;

	/// 共通設定を読み込む.
	XmlElement^ commonElement = (XmlElement^)root->FirstChild;
		XmlElement^ timeStepElement = (XmlElement^)commonElement->FirstChild;
		XmlElement^ effectLengthElement = (XmlElement^)timeStepElement->NextSibling;

		simulationSetting->timeStep = double::Parse( timeStepElement->FirstChild->Value );
		simulationSetting->effectLength = double::Parse( effectLengthElement->FirstChild->Value );

	XMLReader reader;
	/// 境界設定を読み込む.
	XmlElement^ boundaryElement = (XmlElement^)commonElement->NextSibling;
	{
		XmlElement^ boxElement = (XmlElement^)boundaryElement->FirstChild;
		const Box& boundaryBox = reader.readBox( boxElement );
		simulationSetting->boundaryBox = boundaryBox;
	}

	/// オブジェクト設定を読み込む.
	XmlElement^ objectElement = (XmlElement^)boundaryElement->NextSibling;
	for each( XmlElement^ element in objectElement->ChildNodes ) {
		XmlElement^ typeElement = (XmlElement^)element->FirstChild;
		XmlElement^ boxElement = (XmlElement^)typeElement->NextSibling;
		const Box& box = reader.readBox( boxElement );
		XmlElement^ densityElement = (XmlElement^)boxElement->NextSibling;
		XmlElement^ pressureElement = (XmlElement^)densityElement->NextSibling;
		XmlElement^ viscosityElement = (XmlElement^)pressureElement->NextSibling;
		XmlElement^ divideElement = (XmlElement^)viscosityElement->NextSibling;

		const int type = int::Parse( typeElement->FirstChild->Value );
		const double density = double::Parse( densityElement->FirstChild->Value );
		const double pressure = double::Parse( pressureElement->FirstChild->Value );
		const double viscosity = double::Parse( viscosityElement->FirstChild->Value );
		const double divide = double::Parse( divideElement->FirstChild->Value );

		PhysicsObjectCondition* condition = 
			new PhysicsObjectCondition( box, density, divide, pressure, viscosity, (PhysicsObjectCondition::ObjectType)type );

		factory->createPhysicsObject( *condition, SimulationSetting::get()->effectLength );
	}
	return true;
}