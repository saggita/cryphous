#ifndef __COLOR_XYZ_H__
#define __COLOR_XYZ_H__

#include "ColorRGBA.h"

namespace Amorphous{
	namespace Color{

class ColorXYZ
{
public:

	ColorXYZ(): x(0.0), y(0.0), z(0.0){};

	ColorXYZ(double x, double y, double z): x(x), y(y), z(z){};

	ColorXYZ(const ColorRGBA<>& color4d);

	ColorRGBA<> convertToRGB() const;

	~ColorXYZ(void){};

	double getX() const { return x; }

	double getY() const { return y; }

	double getZ() const { return z; }

private:

	Geom::Matrix3d<> getToRGBMatrix() const;

	Geom::Matrix3d<> getToXYZMatrix() const;

	double x;
	double y;
	double z;
};

	}
}
#endif __COLOR_XYZ_H__