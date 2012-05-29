#pragma once

namespace Crystal {
	namespace Geom {
		class Box;
	}
	namespace Graphics {
		class Color4d;
	}
	namespace Command {

ref class XMLReader
{
public:
	XMLReader(void){};

	Geom::Box readBox(System::Xml::XmlElement^ boxElement);

	Graphics::Color4d readColor(System::Xml::XmlElement^ colorElement);
};

	}
}