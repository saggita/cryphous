#pragma once

namespace Crystal {
	namespace Geom {
		class Box;
	}
	namespace Graphics {
		class Color4d;
	}
	namespace Command {

ref class XMLWriter
{
public:
	XMLWriter(System::Xml::XmlDocument^ doc) :
	  doc( doc) {};

	  System::Xml::XmlElement^ write(const Geom::Box& box);

	  System::Xml::XmlElement^ write(const Graphics::Color4d& color);

private:
	System::Xml::XmlDocument^ doc;
};

	}
}