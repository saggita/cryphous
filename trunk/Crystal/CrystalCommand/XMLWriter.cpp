#include "XMLWriter.h"

#include "../CrystalGeom/Box.h"

#include "../CrystalGraphics/Color4d.h"

using namespace Crystal::Geom;
using namespace Crystal::Graphics;
using namespace Crystal::Command;

using namespace System::Xml;

XmlElement^ XMLWriter::write(const Box& box)
{
	XmlElement^ boxElement = doc->CreateElement("box");
	{
		XmlElement^ minElement = doc->CreateElement("min");
		{
			XmlElement^ minXElement = doc->CreateElement("x");
			minXElement->AppendChild( doc->CreateTextNode( box.getMinX().ToString() ) );
			minElement->AppendChild( minXElement );

			XmlElement^ minYElement = doc->CreateElement("y");
			minYElement->AppendChild( doc->CreateTextNode( box.getMinY().ToString() ) );
			minElement->AppendChild( minYElement );

			XmlElement^ minZElement = doc->CreateElement("z");
			minZElement->AppendChild( doc->CreateTextNode( box.getMinZ().ToString() ) );
			minElement->AppendChild( minZElement );
		}
		boxElement->AppendChild( minElement );

		XmlElement^ maxElement = doc->CreateElement("max");
		{
			XmlElement^ maxXElement = doc->CreateElement("x");
			maxXElement->AppendChild( doc->CreateTextNode( box.getMaxX().ToString() ) );
			maxElement->AppendChild( maxXElement );

			XmlElement^ maxYElement = doc->CreateElement("y");
			maxYElement->AppendChild( doc->CreateTextNode( box.getMaxY().ToString() ) );
			maxElement->AppendChild( maxYElement );

			XmlElement^ maxZElement = doc->CreateElement("z");
			maxZElement->AppendChild( doc->CreateTextNode( box.getMaxZ().ToString() ) );
			maxElement->AppendChild( maxZElement );
		}
		boxElement->AppendChild( maxElement );
	}
	return boxElement;
}

XmlElement^ XMLWriter::write(const Color4d& color)
{
	XmlElement^ colorElement = doc->CreateElement("color");
	{
		XmlElement^ redElement = doc->CreateElement("red");
		redElement->AppendChild( doc->CreateTextNode( color.getRed().ToString() ) );
		colorElement->AppendChild( redElement );

		XmlElement^ greenElement = doc->CreateElement("green");
		greenElement->AppendChild( doc->CreateTextNode( color.getGreen().ToString() ) );
		colorElement->AppendChild( greenElement );

		XmlElement^ blueElement = doc->CreateElement("blue");
		blueElement->AppendChild( doc->CreateTextNode( color.getBlue().ToString() ) );
		colorElement->AppendChild( blueElement );
	}
	return colorElement;
}