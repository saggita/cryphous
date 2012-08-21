#ifndef __COLOR_ADAPTOR_H__
#define __COLOR_ADAPTOR_H__

#include "ColorCreatorBase.h"

namespace Crystal {
	namespace Color {
		class ColorLMS;

class ColorAdaptor : public ColorCreatorBase
{
protected:
	ColorAdaptor(const double whitePointTemperature);

	~ColorAdaptor(void);

public:

	static ColorAdaptor* get(){
		static ColorAdaptor adaptor(3000.0);
		return &adaptor;
	}

private:
	Geom::Matrix3d getAdaptMatrix() const;

	ColorLMS getWhitePointLMS() const;

	Geom::Matrix3d getWhitePointLMSMatrix() const;

	virtual ColorRGBA<> getColor(const double temperature) const;

private:
	const double whitePointTemperature;
};

	}
}
#endif __COLOR_ADAPTOR_H__