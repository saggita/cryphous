#include "Space3d.h"

#include <cassert>

using namespace Crystal::Geom;

Space3d::Space3d(const Vector3d& basisX, const Vector3d& basisY) :
basisX( basisX),
basisY( basisY),
basisZ( basisX.getOuterProduct( basisY) )
{
}

Space3d::Space3d(const Vector3d& basisX, const Vector3d& basisY, const Vector3d& basisZ) :
basisX( basisX),
basisY( basisY),
basisZ( basisZ)
{
}

Space3d::~Space3d(void)
{
}

bool Space3d::isValid() const
{
	return isRightHanded() || isLeftHanded();
}

bool Space3d::isRightHanded() const
{
	return basisZ == basisX.getOuterProduct( basisY);
}

bool Space3d::isLeftHanded() const
{
	return basisZ == basisY.getOuterProduct( basisX);
}