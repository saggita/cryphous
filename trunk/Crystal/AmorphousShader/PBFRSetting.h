#ifndef __PBFR_SETTING_H__
#define __PBFR_SETTING_H__

namespace Crystal{
	namespace Shader{

class PBFRSetting{
public:
	PBFRSetting() :
	  pointSize( 5.0f ),
	  repeatLevel( 10 ),
	  alphaThreshold( 0.2f ),
	  pointAlpha( 1.0f ),
	  distribute( 0.03f ),
	  billboard( false ),
	  drawBoundingBox( true),
	  backGroundIntensity( 0.5f)
	{};

	float pointSize;
	int repeatLevel;
	float alphaThreshold;
	float pointAlpha;
	float distribute;
	bool billboard;
	
	bool drawBoundingBox;
	float backGroundIntensity;
};

	}
}

#endif