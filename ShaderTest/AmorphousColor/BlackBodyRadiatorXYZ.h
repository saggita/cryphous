#ifndef __BLACK_BODY_RADIATOR_XYZ_H__
#define __BLACK_BODY_RADIATOR_XYZ_H__

#include "ColorCreatorBase.h"

namespace Amorphous{
	namespace Color {

class BlackBodyRadiatorXYZ : public ColorCreatorBase
{
private:
	BlackBodyRadiatorXYZ(void);

	~BlackBodyRadiatorXYZ(void);

public:
	static BlackBodyRadiatorXYZ* get() {
		static BlackBodyRadiatorXYZ radiator;
		return &radiator;
	}

private:
	virtual ColorRGBA<> getColor(const double temperature) const;

	double getRadiance(const double temperature, const double waveLength) const;
};

	}
}
#endif __BLACK_BODY_RADIATOR_XYZ_H__