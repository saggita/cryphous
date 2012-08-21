#ifndef __RBFR_H__
#define __PBFR_H__

#include <boost/noncopyable.hpp>
#include <vector>
#include <list>
#include <memory>

#include "FlameRendererBase.h"

namespace Crystal{
	namespace Shader{
		class BillboardRenderer;
		class CompositeRenderer;
		class BackGroundRenderer;

class FlameRenderer : public FlameRendererBase
{
public:
	FlameRenderer(const int width, const int height, const PBFRSetting& setting);

	~FlameRenderer();

	virtual bool isBillboard(){ return true; }

protected:

	virtual void onRender();

	virtual void onInit();

private:
	BillboardRenderer* billboardRenderer;
	CompositeRenderer* compositeRenderer;
	std::vector<double> points;
};

	}
}
#endif