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
	  blurRatio( 0.85f ),
	  pointAlpha( 1.0f ),
	  distribute( 0.03f ),
	  billboard( false ),
	  drawBoundingBox( true),
	  smokeThreshold( 1000.0),
	  smokeAlpha( 1.0),
	  smokeIntensity( 0.5),
	  backGroundIntensity( 0.5f)
	{};

	float pointSize;
	int repeatLevel;
	float alphaThreshold;
	float blurRatio;
	float pointAlpha;
	float distribute;
	bool billboard;
	
	bool drawBoundingBox;
	double smokeThreshold;
	double smokeAlpha;
	double smokeIntensity;
	float backGroundIntensity;
};

	}
}

#endif