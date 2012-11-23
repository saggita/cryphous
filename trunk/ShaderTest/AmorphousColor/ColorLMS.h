#ifndef __COLOR_LMS_H__
#define __COLOR_LMS_H__

namespace Amorphous {
	namespace Color {
		class ColorXYZ;

class ColorLMS
{
public:
	ColorLMS(const double l, const double m, const double s);

	ColorLMS(const ColorXYZ& colorXYZ);

	~ColorLMS(void);

	ColorXYZ getColorXYZ() const;

	double getL() const { return l; }

	double getM() const { return m; }

	double getS() const { return s; }

private:
	double l;
	double m;
	double s;

public:

	static Geom::Matrix3d<> getToLMSMatrix();

	static Geom::Matrix3d<> getToXYZMatrix();
};

	}
}
#endif __COLOR_LMS_H__