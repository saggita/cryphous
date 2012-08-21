#ifndef __RBFR_H__
#define __PBFR_H__

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>

#include "FlameRendererBase.h"

namespace Crystal{
	namespace Shader{
		class PointRenderer;
		class CompositeRenderer;
		class BackGroundRenderer;

class PBFR : public FlameRendererBase
{
public:
	PBFR(const int width, const int height, const PBFRSetting& setting);

	~PBFR();

	virtual bool isBillboard(){ return false; }

protected:

	virtual void onRender();

	virtual void onInit();

private:

	PointRenderer* pointRenderer;
	CompositeRenderer* compositeRenderer;
	std::vector<double> points;
};

	}
}
#endif