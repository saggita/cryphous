#ifndef __CRYSTAL_SHADER_COLOR_MAP_H__
#define __CRYSTAL_SHADER_COLOR_MAP_H__

#include <map>
#include "Color.h"

#include "ColorMap.h"

namespace Crystal{
	namespace Shader{

#include <string>

enum Unit{
	Meter;
	KGPerSQUARE;
};

class PhysicsValue{
public:
	float get() const { return value; }
private:
	float value;
	Unit unit;
};

typedef std::pair<PhysicsValue, Color> PhysicsValueColorPair;
typedef std::map<PhysicsValue, Color> PhysicsValueColorMap;

#include <vector>

class ColorMap
{
public:
	ColorMap(){};

	void build(const PhysicsValueColorMap& map, const unsigned int resolution) {
		/*for( const PhysicsValueColorPair& pair : map ) {
			pair.first.get();
		}*/
	}

	Color getColor(const float value) const {
		return getNearestColor();
	}

	getResolution() const {
		return colors.size();
	}

private:

	Color getNearestColor(const float value) const {
		return colors( getNormalized(value) * getResolution() );
	}

	float getNormalized(const float value) const {
		return (value - min) / (max - min)
	}

	std::vector<Color> colors;
	float max;
	float min;
	//PhysicsValueColorMap map;
};

	}
}

#endif