#ifndef __COLOR_CREATOR_BASE_H__
#define __COLOR_CREATOR_BASE_H__

#include "ColorRGBA.h"
#include <vector>

namespace Amorphous{
	namespace Color{

class ColorCreatorBase
{
public:
	ColorCreatorBase(void);

	~ColorCreatorBase(void);

	virtual ColorRGBA<> getColorFromCash(const double temperature) const;

protected:
	void createColorCash(const double minTemperature, const double maxTemperature);

private:
	virtual ColorRGBA<> getColor(const double temperature) const = 0;

private:
	const double temperatureInterval;
	std::vector<ColorRGBA<>> colorCash;
};
	}
}

#endif