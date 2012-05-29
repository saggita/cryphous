#ifndef __ENFORCER_BASE_H__
#define __ENFORCER_BASE_H__

namespace Crystal{
	namespace Physics{
		class PhysicsObject;

class EnforcerBase
{
public:
	EnforcerBase(void){};

	virtual ~EnforcerBase(void){};

	virtual void enforce(PhysicsObject* object, const double proceedTime){};
};

	}
}

#endif
