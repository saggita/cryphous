#include "XMLReader.h"

#include "../CrystalGeom/Vector3d.h"
#include "../CrystalGeom/Box.h"

#include "../CrystalGraphics/Color4d.h"

using namespace Crystal::Geom;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System::Xml;

Box XMLReader::readBox(System::Xml::XmlElement^ boxElement)
{
	XmlElement^ minElement = (XmlElement^)boxElement->FirstChild;
		XmlElement^ minXElement = (XmlElement^)minElement->FirstChild;
		XmlElement^ minYElement = (XmlElement^)minXElement->NextSibling;
		XmlElement^ minZElement = (XmlElement^)minYElement->NextSibling;
	XmlElement^ maxElement = (XmlElement^)minElement->NextSibling;
		XmlElement^ maxXElement = (XmlElement^)maxElement->FirstChild;
		XmlElement^ maxYElement = (XmlElement^)maxXElement->NextSibling;
		XmlElement^ maxZElement = (XmlElement^)maxYElement->NextSibling;

	const double minX = double::Parse( minXElement->FirstChild->Value );
	const double minY = double::Parse( minYElement->FirstChild->Value );
	const double minZ = double::Parse( minZElement->FirstChild->Value );

	const double maxX = double::Parse( maxXElement->FirstChild->Value );
	const double maxY = double::Parse( maxYElement->FirstChild->Value );
	const double maxZ = double::Parse( maxZElement->FirstChild->Value );

	return Box( Vector3d( minX, minY, minZ), Vector3d( maxX, maxY, maxZ ) );
}

Color4d XMLReader::readColor(System::Xml::XmlElement ^colorElement)
{
	XmlElement^ redElement = (XmlElement^)colorElement->FirstChild;
	XmlElement^ greenElement = (XmlElement^)redElement->NextSibling;
	XmlElement^ blueElement = (XmlElement^)greenElement->NextSibling;

	const double red = double::Parse( redElement->FirstChild->Value );
	const double green = double::Parse( greenElement->FirstChild->Value );
	const double blue = double::Parse( blueElement->FirstChild->Value );

	return Color4d( red, green, blue );
}