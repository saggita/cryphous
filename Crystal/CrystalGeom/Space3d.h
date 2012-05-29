#ifndef __SPACE_3D_H__
#define __SPACE_3D_H__

#include "Vector3d.h"

namespace Crystal {
	namespace Geom {

class Space3d
{
public:
	Space3d(const Vector3d& basisX, const Vector3d& basisY);

	Space3d(const Vector3d& basisX, const Vector3d& basisY, const Vector3d& basisZ);

	~Space3d(void);

	bool isValid() const;

	bool isLeftHanded() const;

	bool isRightHanded() const;

	Vector3d getBasisX() const { return basisX; }

	Vector3d getBasisY() const { return basisY; }

	Vector3d getBasisZ() const { return basisZ; }

private:
	const Vector3d basisX;
	const Vector3d basisY;
	const Vector3d basisZ;
};

	}
}

#endif